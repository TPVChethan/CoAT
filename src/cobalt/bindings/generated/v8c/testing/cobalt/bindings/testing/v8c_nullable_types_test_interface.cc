

// Copyright 2018 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// clang-format off

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/v8c/templates/interface.cc.template

#include "cobalt/bindings/testing/v8c_nullable_types_test_interface.h"

#include "base/debug/trace_event.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/global_environment.h"
#include "cobalt/script/script_value.h"
#include "cobalt/script/value_handle.h"
#include "cobalt/bindings/testing/arbitrary_interface.h"
#include "cobalt/bindings/testing/v8c_arbitrary_interface.h"

#include "v8c_gen_type_conversion.h"

#include "cobalt/script/callback_interface_traits.h"
#include "cobalt/script/v8c/callback_function_conversion.h"
#include "cobalt/script/v8c/conversion_helpers.h"
#include "cobalt/script/v8c/entry_scope.h"
#include "cobalt/script/v8c/native_promise.h"
#include "cobalt/script/v8c/type_traits.h"
#include "cobalt/script/v8c/v8c_callback_function.h"
#include "cobalt/script/v8c/v8c_callback_interface_holder.h"
#include "cobalt/script/v8c/v8c_exception_state.h"
#include "cobalt/script/v8c/v8c_global_environment.h"
#include "cobalt/script/v8c/v8c_value_handle.h"
#include "cobalt/script/v8c/wrapper_private.h"
#include "v8/include/v8.h"


namespace {
using cobalt::bindings::testing::NullableTypesTestInterface;
using cobalt::bindings::testing::V8cNullableTypesTestInterface;
using cobalt::bindings::testing::ArbitraryInterface;
using cobalt::bindings::testing::V8cArbitraryInterface;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::GlobalEnvironment;
using cobalt::script::ScriptValue;
using cobalt::script::ValueHandle;
using cobalt::script::ValueHandle;
using cobalt::script::ValueHandleHolder;
using cobalt::script::Wrappable;

using cobalt::script::v8c::EntryScope;
using cobalt::script::v8c::EscapableEntryScope;
using cobalt::script::v8c::FromJSValue;
using cobalt::script::v8c::InterfaceData;
using cobalt::script::v8c::kConversionFlagClamped;
using cobalt::script::v8c::kConversionFlagNullable;
using cobalt::script::v8c::kConversionFlagObjectOnly;
using cobalt::script::v8c::kConversionFlagRestricted;
using cobalt::script::v8c::kConversionFlagTreatNullAsEmptyString;
using cobalt::script::v8c::kConversionFlagTreatUndefinedAsEmptyString;
using cobalt::script::v8c::kNoConversionFlags;
using cobalt::script::v8c::ToJSValue;
using cobalt::script::v8c::TypeTraits;
using cobalt::script::v8c::V8cExceptionState;
using cobalt::script::v8c::V8cGlobalEnvironment;
using cobalt::script::v8c::WrapperFactory;
using cobalt::script::v8c::WrapperPrivate;

v8::Local<v8::Object> DummyFunctor(v8::Isolate*, const scoped_refptr<Wrappable>&) {
  NOTIMPLEMENTED();
  return {};
}

}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {


namespace {



void nullableBooleanPropertyAttributeGetter(
    v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();


  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->nullable_boolean_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }
}

void nullableBooleanPropertyAttributeSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> v8_value,
    const v8::PropertyCallbackInfo<void>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();

  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  TypeTraits<base::optional<bool > >::ConversionType value;
  FromJSValue(isolate, v8_value, (kConversionFlagNullable), &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->set_nullable_boolean_property(value);
  result_value = v8::Undefined(isolate);
  return;
}

void nullableNumericPropertyAttributeGetter(
    v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();


  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->nullable_numeric_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }
}

void nullableNumericPropertyAttributeSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> v8_value,
    const v8::PropertyCallbackInfo<void>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();

  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  TypeTraits<base::optional<int32_t > >::ConversionType value;
  FromJSValue(isolate, v8_value, (kConversionFlagNullable), &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->set_nullable_numeric_property(value);
  result_value = v8::Undefined(isolate);
  return;
}

void nullableStringPropertyAttributeGetter(
    v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();


  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->nullable_string_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }
}

void nullableStringPropertyAttributeSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> v8_value,
    const v8::PropertyCallbackInfo<void>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();

  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  TypeTraits<base::optional<std::string > >::ConversionType value;
  FromJSValue(isolate, v8_value, (kConversionFlagNullable), &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->set_nullable_string_property(value);
  result_value = v8::Undefined(isolate);
  return;
}

void nullableObjectPropertyAttributeGetter(
    v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();


  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->nullable_object_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }
}

void nullableObjectPropertyAttributeSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> v8_value,
    const v8::PropertyCallbackInfo<void>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();

  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  TypeTraits<scoped_refptr<ArbitraryInterface> >::ConversionType value;
  FromJSValue(isolate, v8_value, (kConversionFlagNullable), &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->set_nullable_object_property(value);
  result_value = v8::Undefined(isolate);
  return;
}



void nullableBooleanArgumentMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  const size_t kMinArguments = 1;
  if (info.Length() < kMinArguments) {
    exception_state.SetSimpleException(script::kInvalidNumberOfArguments);
    return;
  }
  // Non-optional arguments
  TypeTraits<base::optional<bool > >::ConversionType arg;
  DCHECK_LT(0, info.Length());
  v8::Local<v8::Value> non_optional_value0 = info[0];
  FromJSValue(isolate,
              non_optional_value0,
              (kConversionFlagNullable),
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->NullableBooleanArgument(arg);
  result_value = v8::Undefined(isolate);

}



void nullableBooleanOperationMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->NullableBooleanOperation(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }

}



void nullableNumericArgumentMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  const size_t kMinArguments = 1;
  if (info.Length() < kMinArguments) {
    exception_state.SetSimpleException(script::kInvalidNumberOfArguments);
    return;
  }
  // Non-optional arguments
  TypeTraits<base::optional<int32_t > >::ConversionType arg;
  DCHECK_LT(0, info.Length());
  v8::Local<v8::Value> non_optional_value0 = info[0];
  FromJSValue(isolate,
              non_optional_value0,
              (kConversionFlagNullable),
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->NullableNumericArgument(arg);
  result_value = v8::Undefined(isolate);

}



void nullableNumericOperationMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->NullableNumericOperation(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }

}



void nullableObjectArgumentMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  const size_t kMinArguments = 1;
  if (info.Length() < kMinArguments) {
    exception_state.SetSimpleException(script::kInvalidNumberOfArguments);
    return;
  }
  // Non-optional arguments
  TypeTraits<scoped_refptr<ArbitraryInterface> >::ConversionType arg;
  DCHECK_LT(0, info.Length());
  v8::Local<v8::Value> non_optional_value0 = info[0];
  FromJSValue(isolate,
              non_optional_value0,
              (kConversionFlagNullable),
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->NullableObjectArgument(arg);
  result_value = v8::Undefined(isolate);

}



void nullableObjectOperationMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->NullableObjectOperation(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }

}



void nullableStringArgumentMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();
  const size_t kMinArguments = 1;
  if (info.Length() < kMinArguments) {
    exception_state.SetSimpleException(script::kInvalidNumberOfArguments);
    return;
  }
  // Non-optional arguments
  TypeTraits<base::optional<std::string > >::ConversionType arg;
  DCHECK_LT(0, info.Length());
  v8::Local<v8::Value> non_optional_value0 = info[0];
  FromJSValue(isolate,
              non_optional_value0,
              (kConversionFlagNullable),
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return;
  }

  impl->NullableStringArgument(arg);
  result_value = v8::Undefined(isolate);

}



void nullableStringOperationMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::Local<v8::Object> object = info.This();
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<NullableTypesTestInterface>())) {
    V8cExceptionState exception(isolate);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return;
  }
  V8cExceptionState exception_state{isolate};
  v8::Local<v8::Value> result_value;

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromWrapperObject(object);
  if (!wrapper_private) {
    NOTIMPLEMENTED();
    return;
  }
  NullableTypesTestInterface* impl =
      wrapper_private->wrappable<NullableTypesTestInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(isolate,
              impl->NullableStringOperation(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    info.GetReturnValue().Set(result_value);
  }

}


void InitializeTemplateAndInterfaceObject(v8::Isolate* isolate, InterfaceData* interface_data) {
  v8::Local<v8::FunctionTemplate> function_template = v8::FunctionTemplate::New(isolate);
  function_template->SetClassName(
    v8::String::NewFromUtf8(isolate, "NullableTypesTestInterface",
        v8::NewStringType::kInternalized).ToLocalChecked());
  v8::Local<v8::ObjectTemplate> instance_template = function_template->InstanceTemplate();
  instance_template->SetInternalFieldCount(WrapperPrivate::kInternalFieldCount);


  v8::Local<v8::ObjectTemplate> prototype_template = function_template->PrototypeTemplate();


  instance_template->SetAccessor(
    v8::String::NewFromUtf8(isolate, "nullableBooleanProperty",
                              v8::NewStringType::kInternalized)
          .ToLocalChecked(),
    nullableBooleanPropertyAttributeGetter
    ,nullableBooleanPropertyAttributeSetter
  );
  instance_template->SetAccessor(
    v8::String::NewFromUtf8(isolate, "nullableNumericProperty",
                              v8::NewStringType::kInternalized)
          .ToLocalChecked(),
    nullableNumericPropertyAttributeGetter
    ,nullableNumericPropertyAttributeSetter
  );
  instance_template->SetAccessor(
    v8::String::NewFromUtf8(isolate, "nullableStringProperty",
                              v8::NewStringType::kInternalized)
          .ToLocalChecked(),
    nullableStringPropertyAttributeGetter
    ,nullableStringPropertyAttributeSetter
  );
  instance_template->SetAccessor(
    v8::String::NewFromUtf8(isolate, "nullableObjectProperty",
                              v8::NewStringType::kInternalized)
          .ToLocalChecked(),
    nullableObjectPropertyAttributeGetter
    ,nullableObjectPropertyAttributeSetter
  );

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableBooleanArgumentMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableBooleanArgument",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableBooleanOperationMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableBooleanOperation",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableNumericArgumentMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableNumericArgument",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableNumericOperationMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableNumericOperation",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableObjectArgumentMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableObjectArgument",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableObjectOperationMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableObjectOperation",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableStringArgumentMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableStringArgument",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }

  {
    v8::Local<v8::FunctionTemplate> method_template = v8::FunctionTemplate::New(isolate, nullableStringOperationMethod);
    method_template->RemovePrototype();
    prototype_template->Set(
        v8::String::NewFromUtf8(
            isolate,
            "nullableStringOperation",
            v8::NewStringType::kInternalized).ToLocalChecked(),
        method_template);
  }


  interface_data->function_template.Set(isolate, function_template);
}

inline InterfaceData* GetInterfaceData(V8cGlobalEnvironment* global_environment) {
  const int kInterfaceUniqueId = 37;
  // By convention, the |V8cGlobalEnvironment| that we are associated with
  // will hold our |InterfaceData| at index |kInterfaceUniqueId|, as we asked
  // for it to be there in the first place, and could not have conflicted with
  // any other interface.
  return global_environment->GetInterfaceData(kInterfaceUniqueId);
}

}  // namespace

v8::Local<v8::Object> V8cNullableTypesTestInterface::CreateWrapper(v8::Isolate* isolate, const scoped_refptr<Wrappable>& wrappable) {
  EscapableEntryScope entry_scope(isolate);
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  InterfaceData* interface_data = GetInterfaceData(global_environment);
  if (interface_data->function_template.IsEmpty()) {
    InitializeTemplateAndInterfaceObject(isolate, interface_data);
  }
  DCHECK(!interface_data->function_template.IsEmpty());

  v8::Local<v8::FunctionTemplate> function_template = interface_data->function_template.Get(isolate);
  DCHECK(function_template->InstanceTemplate()->InternalFieldCount() == WrapperPrivate::kInternalFieldCount);
  v8::Local<v8::Object> object = function_template->InstanceTemplate()->NewInstance(context).ToLocalChecked();
  DCHECK(object->InternalFieldCount() == WrapperPrivate::kInternalFieldCount);

  // This |WrapperPrivate|'s lifetime will be managed by V8.
  new WrapperPrivate(isolate, wrappable, object);
  return entry_scope.Escape(object);
}

v8::Local<v8::FunctionTemplate> V8cNullableTypesTestInterface::CreateTemplate(v8::Isolate* isolate) {
  V8cGlobalEnvironment* global_environment = V8cGlobalEnvironment::GetFromIsolate(isolate);
  InterfaceData* interface_data = GetInterfaceData(global_environment);
  if (interface_data->function_template.IsEmpty()) {
    InitializeTemplateAndInterfaceObject(isolate, interface_data);
  }

  return interface_data->function_template.Get(isolate);
}


}  // namespace testing
}  // namespace bindings
}  // namespace cobalt


