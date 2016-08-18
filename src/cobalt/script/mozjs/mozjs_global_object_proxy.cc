/*
 * Copyright 2016 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "cobalt/script/mozjs/mozjs_global_object_proxy.h"

#include <utility>

#include "base/stringprintf.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/mozjs/conversion_helpers.h"
#include "cobalt/script/mozjs/mozjs_exception_state.h"
#include "cobalt/script/mozjs/mozjs_source_code.h"
#include "third_party/mozjs/js/src/jsfriendapi.h"
#include "third_party/mozjs/js/src/jsfun.h"
#include "third_party/mozjs/js/src/jsobj.h"

// A note on CompartmentOptions and Principals.
// These concepts are an integral part of Gecko's security implementation, but
// we don't need to be concerned with this for Cobalt.
//
// Compartments are separate regions of memory. Each global object has a
// separate compartment. Since Cobalt will use a different JSRuntime for each
// thread and each global object cannot access another directly anyways, this
// shouldn't be an issue even in our development workflow.
// If we support multiple windows in some form, a cross-compartment wrapper is
// needed to access another global object. If they are same-origin this is
// simpler.
// Principals (or Security principals) are used to determine the security
// relationship between two compartments. Since Cobalt does not have multiple
// global objects there is no need to define Security principals. Even so,
// it we'd likely want to implement such a security policy in an engine
// independent way anyways.
// See https://developer.mozilla.org/en-US/docs/Mozilla/Gecko/Script_security

namespace cobalt {
namespace script {
namespace mozjs {
namespace {
// Class definition for global object with no bindings.
JSClass simple_global_class = {
    "global",               // name
    JSCLASS_GLOBAL_FLAGS,   // flags
    JS_PropertyStub,        // addProperty
    JS_DeletePropertyStub,  // delProperty
    JS_PropertyStub,        // getProperty
    JS_StrictPropertyStub,  // setProperty
    JS_EnumerateStub,       // enumerate
    JS_ResolveStub,         // resolve
    JS_ConvertStub,         // convert
};

// 8192 is the recommended default value.
const uint32_t kStackChunkSize = 8192;

// This is the default in the spidermonkey shell.
const uint32_t kMaxCodeCacheBytes = 16 * 1024 * 1024;
}  // namespace

MozjsGlobalObjectProxy::MozjsGlobalObjectProxy(JSRuntime* runtime)
    : context_(NULL),
      cached_interface_data_deleter_(&cached_interface_data_),
      context_destructor_(&context_),
      environment_settings_(NULL),
      last_error_message_(NULL),
      eval_enabled_(false) {
  context_ = JS_NewContext(runtime, kStackChunkSize);
  DCHECK(context_);
  // Set a pointer to this class inside the JSContext.
  JS_SetContextPrivate(context_, this);

  JS_SetGCParameterForThread(context_, JSGC_MAX_CODE_CACHE_BYTES,
                             kMaxCodeCacheBytes);

  uint32_t options =
      JSOPTION_TYPE_INFERENCE |
      JSOPTION_VAROBJFIX |       // Recommended to enable this in the API docs.
      JSOPTION_COMPILE_N_GO |    // Compiled scripts will be run only once.
      JSOPTION_UNROOTED_GLOBAL;  // Global handle must be visited to ensure it
                                 // is not GC'd.
#if SB_CAN(MAP_EXECUTABLE_MEMORY)
  options |= JSOPTION_BASELINE |  // Enable baseline compiler.
             JSOPTION_ION;        // Enable IonMonkey
#endif
#if !defined(COBALT_BUILD_TYPE_GOLD) && !defined(COBALT_BUILD_TYPE_QA)
  options |= JSOPTION_EXTRA_WARNINGS;
#endif
  JS_SetOptions(context_, options);

  JS_SetErrorReporter(context_, &MozjsGlobalObjectProxy::ReportErrorHandler);

  wrapper_factory_.reset(new WrapperFactory(context_));
  JS_AddExtraGCRootsTracer(runtime, TraceFunction, this);
}

MozjsGlobalObjectProxy::~MozjsGlobalObjectProxy() {
  DCHECK(thread_checker_.CalledOnValidThread());
  JS_RemoveExtraGCRootsTracer(JS_GetRuntime(context_), TraceFunction, this);
}

void MozjsGlobalObjectProxy::CreateGlobalObject() {
  DCHECK(thread_checker_.CalledOnValidThread());
  DCHECK(!global_object_);

  // The global object is automatically rooted unless the
  // JSOPTION_UNROOTED_GLOBAL option is set.
  JSAutoRequest auto_request(context_);

  // NULL JSPrincipals and default JS::CompartmentOptions. See the comment
  // above for rationale.
  JS::RootedObject global_object(
      context_, JS_NewGlobalObject(context_, &simple_global_class, NULL));
  DCHECK(global_object);

  // Initialize standard JS constructors prototypes and top-level functions such
  // as Object, isNan, etc.
  JSAutoCompartment auto_compartment(context_, global_object);
  bool success = JS_InitStandardClasses(context_, global_object);
  DCHECK(success);
  SetGlobalObject(global_object);
}

bool MozjsGlobalObjectProxy::EvaluateScript(
    const scoped_refptr<SourceCode>& source_code,
    std::string* out_result_utf8) {
  DCHECK(thread_checker_.CalledOnValidThread());
  MozjsSourceCode* mozjs_source_code =
      base::polymorphic_downcast<MozjsSourceCode*>(source_code.get());

  const std::string& script = mozjs_source_code->source_utf8();
  const base::SourceLocation location = mozjs_source_code->location();

  JSAutoRequest auto_request(context_);
  JSAutoCompartment auto_comparment(context_, global_object_);
  JS::RootedValue result_value(context_);
  std::string error_message;
  last_error_message_ = &error_message;
  bool success = JS_EvaluateScript(
      context_, global_object_, script.c_str(), script.size(),
      location.file_path.c_str(), location.line_number, result_value.address());
  if (out_result_utf8) {
    if (success) {
      MozjsExceptionState exception_state(context_);
      FromJSValue(context_, result_value, kNoConversionFlags, &exception_state,
                  out_result_utf8);
    } else {
      *out_result_utf8 = *last_error_message_;
    }
  }
  last_error_message_ = NULL;
  return success;
}

void MozjsGlobalObjectProxy::DisableEval(const std::string& message) {
  DCHECK(thread_checker_.CalledOnValidThread());
  eval_disabled_message_.emplace(message);
  eval_enabled_ = false;
}

void MozjsGlobalObjectProxy::EnableEval() {
  DCHECK(thread_checker_.CalledOnValidThread());
  eval_disabled_message_ = base::nullopt;
  eval_enabled_ = true;
}

void MozjsGlobalObjectProxy::SetReportEvalCallback(
    const base::Closure& report_eval) {
  DCHECK(thread_checker_.CalledOnValidThread());
  report_eval_ = report_eval;
}

void MozjsGlobalObjectProxy::Bind(const std::string& identifier,
                                  const scoped_refptr<Wrappable>& impl) {
  JSAutoRequest auto_request(context_);
  JSAutoCompartment auto_comparment(context_, global_object_);
  JS::RootedObject wrapper_proxy(context_,
                                 wrapper_factory_->GetWrapperProxy(impl));
  JS::Value wrapper_value = OBJECT_TO_JSVAL(wrapper_proxy);
  bool success = JS_SetProperty(context_, global_object_, identifier.c_str(),
                                &wrapper_value);
  DCHECK(success);
}

InterfaceData* MozjsGlobalObjectProxy::GetInterfaceData(intptr_t key) {
  CachedInterfaceData::iterator it = cached_interface_data_.find(key);
  if (it != cached_interface_data_.end()) {
    return it->second;
  }
  return NULL;
}

MozjsGlobalObjectProxy* MozjsGlobalObjectProxy::GetFromContext(
    JSContext* context) {
  MozjsGlobalObjectProxy* global_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
  DCHECK(global_proxy);
  return global_proxy;
}

void MozjsGlobalObjectProxy::CacheInterfaceData(intptr_t key,
                                                InterfaceData* interface_data) {
  std::pair<CachedInterfaceData::iterator, bool> pib =
      cached_interface_data_.insert(std::make_pair(key, interface_data));
  DCHECK(pib.second);
}

void MozjsGlobalObjectProxy::ReportErrorHandler(JSContext* context,
                                                const char* message,
                                                JSErrorReport* report) {
  MozjsGlobalObjectProxy* global_object_proxy = GetFromContext(context);
  std::string error_message;
  if (report->errorNumber == JSMSG_CSP_BLOCKED_EVAL) {
    error_message =
        global_object_proxy->eval_disabled_message_.value_or(message);
  } else {
    error_message = message;
  }

  if (global_object_proxy && global_object_proxy->last_error_message_) {
    *(global_object_proxy->last_error_message_) = error_message;
  } else {
    DLOG(ERROR) << "JS Error: " << error_message;
  }
}

void MozjsGlobalObjectProxy::TraceFunction(JSTracer* trace, void* data) {
  MozjsGlobalObjectProxy* global_object_proxy =
      reinterpret_cast<MozjsGlobalObjectProxy*>(data);
  if (global_object_proxy->global_object_) {
    JS_CallHeapObjectTracer(trace, &global_object_proxy->global_object_,
                            "MozjsGlobalObjectProxy");
  }
  for (CachedInterfaceData::iterator it =
           global_object_proxy->cached_interface_data_.begin();
       it != global_object_proxy->cached_interface_data_.end(); ++it) {
    InterfaceData* data = it->second;
    JS_CallHeapObjectTracer(trace, &data->prototype, "MozjsGlobalObjectProxy");
    JS_CallHeapObjectTracer(trace, &data->interface_object,
                            "MozjsGlobalObjectProxy");
  }
}

JSBool MozjsGlobalObjectProxy::CheckEval(JSContext* context) {
  MozjsGlobalObjectProxy* global_object_proxy = GetFromContext(context);
  DCHECK(global_object_proxy);
  if (!global_object_proxy->report_eval_.is_null()) {
    global_object_proxy->report_eval_.Run();
  }
  return global_object_proxy->eval_enabled_;
}

}  // namespace mozjs
}  // namespace script
}  // namespace cobalt
