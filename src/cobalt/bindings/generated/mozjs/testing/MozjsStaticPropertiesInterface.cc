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

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/mozjs/templates/interface.cc.template

// clang-format off

#include "MozjsStaticPropertiesInterface.h"

#include "base/debug/trace_event.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/global_object_proxy.h"
#include "cobalt/script/opaque_handle.h"
#include "cobalt/script/script_object.h"
#include "MozjsArbitraryInterface.h"
#include "cobalt/bindings/testing/arbitrary_interface.h"

#include "base/lazy_instance.h"
#include "cobalt/script/mozjs/callback_function_conversion.h"
#include "cobalt/script/exception_state.h"
#include "cobalt/script/mozjs/conversion_helpers.h"
#include "cobalt/script/mozjs/mozjs_exception_state.h"
#include "cobalt/script/mozjs/mozjs_callback_function.h"
#include "cobalt/script/mozjs/mozjs_global_object_proxy.h"
#include "cobalt/script/mozjs/mozjs_object_handle.h"
#include "cobalt/script/mozjs/mozjs_property_enumerator.h"
#include "cobalt/script/mozjs/mozjs_user_object_holder.h"
#include "cobalt/script/mozjs/proxy_handler.h"
#include "cobalt/script/mozjs/type_traits.h"
#include "cobalt/script/mozjs/wrapper_factory.h"
#include "cobalt/script/mozjs/wrapper_private.h"
#include "cobalt/script/property_enumerator.h"
#include "third_party/mozjs/js/src/jsapi.h"
#include "third_party/mozjs/js/src/jsfriendapi.h"

namespace {
using cobalt::bindings::testing::StaticPropertiesInterface;
using cobalt::bindings::testing::MozjsStaticPropertiesInterface;
using cobalt::bindings::testing::ArbitraryInterface;
using cobalt::bindings::testing::MozjsArbitraryInterface;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::GlobalObjectProxy;
using cobalt::script::OpaqueHandle;
using cobalt::script::OpaqueHandleHolder;
using cobalt::script::ScriptObject;
using cobalt::script::Wrappable;

using cobalt::script::CallbackFunction;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::ExceptionState;
using cobalt::script::mozjs::FromJSValue;
using cobalt::script::mozjs::kConversionFlagNullable;
using cobalt::script::mozjs::kConversionFlagRestricted;
using cobalt::script::mozjs::kConversionFlagTreatNullAsEmptyString;
using cobalt::script::mozjs::kConversionFlagTreatUndefinedAsEmptyString;
using cobalt::script::mozjs::kNoConversionFlags;
using cobalt::script::mozjs::InterfaceData;
using cobalt::script::mozjs::MozjsCallbackFunction;
using cobalt::script::mozjs::MozjsExceptionState;
using cobalt::script::mozjs::MozjsGlobalObjectProxy;
using cobalt::script::mozjs::MozjsUserObjectHolder;
using cobalt::script::mozjs::MozjsPropertyEnumerator;
using cobalt::script::mozjs::ProxyHandler;
using cobalt::script::mozjs::ToJSValue;
using cobalt::script::mozjs::TypeTraits;
using cobalt::script::mozjs::WrapperPrivate;
using cobalt::script::mozjs::WrapperFactory;
using cobalt::script::Wrappable;
}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {

namespace {

class MozjsStaticPropertiesInterfaceHandler : public ProxyHandler {
 public:
  MozjsStaticPropertiesInterfaceHandler()
      : ProxyHandler(indexed_property_hooks, named_property_hooks) {}

 private:
  static NamedPropertyHooks named_property_hooks;
  static IndexedPropertyHooks indexed_property_hooks;
};

ProxyHandler::NamedPropertyHooks
MozjsStaticPropertiesInterfaceHandler::named_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};
ProxyHandler::IndexedPropertyHooks
MozjsStaticPropertiesInterfaceHandler::indexed_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static base::LazyInstance<MozjsStaticPropertiesInterfaceHandler>
    proxy_handler;

JSBool HasInstance(JSContext *context, JS::HandleObject type,
                   JS::MutableHandleValue vp, JSBool *success) {
  JS::RootedObject global_object(
      context, JS_GetGlobalForObject(context, type));
  DCHECK(global_object);

  JS::RootedObject prototype(
      context, MozjsStaticPropertiesInterface::GetPrototype(context, global_object));

  // |IsDelegate| walks the prototype chain of an object returning true if
  // .prototype is found.
  bool is_delegate;
  if (!IsDelegate(context, prototype, vp, &is_delegate)) {
    *success = false;
    return false;
  }

  *success = is_delegate;
  return true;
}

InterfaceData* CreateCachedInterfaceData() {
  InterfaceData* interface_data = new InterfaceData();
  memset(&interface_data->instance_class_definition, 0,
         sizeof(interface_data->instance_class_definition));
  memset(&interface_data->prototype_class_definition, 0,
         sizeof(interface_data->prototype_class_definition));
  memset(&interface_data->interface_object_class_definition, 0,
         sizeof(interface_data->interface_object_class_definition));

  JSClass* instance_class = &interface_data->instance_class_definition;
  const int kGlobalFlags = 0;
  instance_class->name = "StaticPropertiesInterface";
  instance_class->flags = kGlobalFlags | JSCLASS_HAS_PRIVATE;
  instance_class->addProperty = JS_PropertyStub;
  instance_class->delProperty = JS_DeletePropertyStub;
  instance_class->getProperty = JS_PropertyStub;
  instance_class->setProperty = JS_StrictPropertyStub;
  instance_class->enumerate = JS_EnumerateStub;
  instance_class->resolve = JS_ResolveStub;
  instance_class->convert = JS_ConvertStub;
  // Function to be called before on object of this class is garbage collected.
  instance_class->finalize = &WrapperPrivate::Finalizer;
  // Called to trace objects that can be referenced from this object.
  instance_class->trace = &WrapperPrivate::Trace;

  JSClass* prototype_class = &interface_data->prototype_class_definition;
  prototype_class->name = "StaticPropertiesInterfacePrototype";
  prototype_class->flags = 0;
  prototype_class->addProperty = JS_PropertyStub;
  prototype_class->delProperty = JS_DeletePropertyStub;
  prototype_class->getProperty = JS_PropertyStub;
  prototype_class->setProperty = JS_StrictPropertyStub;
  prototype_class->enumerate = JS_EnumerateStub;
  prototype_class->resolve = JS_ResolveStub;
  prototype_class->convert = JS_ConvertStub;

  JSClass* interface_object_class =
      &interface_data->interface_object_class_definition;
  interface_object_class->name = "StaticPropertiesInterfaceConstructor";
  interface_object_class->flags = 0;
  interface_object_class->addProperty = JS_PropertyStub;
  interface_object_class->delProperty = JS_DeletePropertyStub;
  interface_object_class->getProperty = JS_PropertyStub;
  interface_object_class->setProperty = JS_StrictPropertyStub;
  interface_object_class->enumerate = JS_EnumerateStub;
  interface_object_class->resolve = JS_ResolveStub;
  interface_object_class->convert = JS_ConvertStub;
  interface_object_class->hasInstance = &HasInstance;
  return interface_data;
}

JSBool staticget_staticAttribute(
    JSContext* context, JS::HandleObject object, JS::HandleId id,
    JS::MutableHandleValue vp) {
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  if (!exception_state.is_exception_set()) {
    ToJSValue(context,
              StaticPropertiesInterface::static_attribute(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    vp.set(result_value);
  }
  return !exception_state.is_exception_set();
}

JSBool staticset_staticAttribute(
    JSContext* context, JS::HandleObject object, JS::HandleId id,
    JSBool strict, JS::MutableHandleValue vp) {
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  TypeTraits<std::string >::ConversionType value;
  FromJSValue(context, vp, kNoConversionFlags, &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return false;
  }

  StaticPropertiesInterface::set_static_attribute(value);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction1(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);


  StaticPropertiesInterface::StaticFunction();
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction2(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  const size_t kMinArguments = 1;
  if (args.length() < kMinArguments) {
    exception_state.SetSimpleException(
        script::ExceptionState::kTypeError, "Not enough arguments.");
    return false;
  }
  // Non-optional arguments
  TypeTraits<int32_t >::ConversionType arg;

  DCHECK_LT(0, args.length());
  JS::RootedValue non_optional_value0(
      context, args[0]);
  FromJSValue(context,
              non_optional_value0,
              kNoConversionFlags,
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return false;
  }

  StaticPropertiesInterface::StaticFunction(arg);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction3(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  const size_t kMinArguments = 1;
  if (args.length() < kMinArguments) {
    exception_state.SetSimpleException(
        script::ExceptionState::kTypeError, "Not enough arguments.");
    return false;
  }
  // Non-optional arguments
  TypeTraits<std::string >::ConversionType arg;

  DCHECK_LT(0, args.length());
  JS::RootedValue non_optional_value0(
      context, args[0]);
  FromJSValue(context,
              non_optional_value0,
              kNoConversionFlags,
              &exception_state, &arg);
  if (exception_state.is_exception_set()) {
    return false;
  }

  StaticPropertiesInterface::StaticFunction(arg);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction4(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  const size_t kMinArguments = 3;
  if (args.length() < kMinArguments) {
    exception_state.SetSimpleException(
        script::ExceptionState::kTypeError, "Not enough arguments.");
    return false;
  }
  // Non-optional arguments
  TypeTraits<int32_t >::ConversionType arg1;
  TypeTraits<int32_t >::ConversionType arg2;
  TypeTraits<int32_t >::ConversionType arg3;

  DCHECK_LT(0, args.length());
  JS::RootedValue non_optional_value0(
      context, args[0]);
  FromJSValue(context,
              non_optional_value0,
              kNoConversionFlags,
              &exception_state, &arg1);
  if (exception_state.is_exception_set()) {
    return false;
  }

  DCHECK_LT(1, args.length());
  JS::RootedValue non_optional_value1(
      context, args[1]);
  FromJSValue(context,
              non_optional_value1,
              kNoConversionFlags,
              &exception_state, &arg2);
  if (exception_state.is_exception_set()) {
    return false;
  }

  DCHECK_LT(2, args.length());
  JS::RootedValue non_optional_value2(
      context, args[2]);
  FromJSValue(context,
              non_optional_value2,
              kNoConversionFlags,
              &exception_state, &arg3);
  if (exception_state.is_exception_set()) {
    return false;
  }

  StaticPropertiesInterface::StaticFunction(arg1, arg2, arg3);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction5(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  const size_t kMinArguments = 3;
  if (args.length() < kMinArguments) {
    exception_state.SetSimpleException(
        script::ExceptionState::kTypeError, "Not enough arguments.");
    return false;
  }
  // Non-optional arguments
  TypeTraits<int32_t >::ConversionType arg1;
  TypeTraits<int32_t >::ConversionType arg2;
  TypeTraits<scoped_refptr<ArbitraryInterface> >::ConversionType arg3;

  DCHECK_LT(0, args.length());
  JS::RootedValue non_optional_value0(
      context, args[0]);
  FromJSValue(context,
              non_optional_value0,
              kNoConversionFlags,
              &exception_state, &arg1);
  if (exception_state.is_exception_set()) {
    return false;
  }

  DCHECK_LT(1, args.length());
  JS::RootedValue non_optional_value1(
      context, args[1]);
  FromJSValue(context,
              non_optional_value1,
              kNoConversionFlags,
              &exception_state, &arg2);
  if (exception_state.is_exception_set()) {
    return false;
  }

  DCHECK_LT(2, args.length());
  JS::RootedValue non_optional_value2(
      context, args[2]);
  FromJSValue(context,
              non_optional_value2,
              kNoConversionFlags,
              &exception_state, &arg3);
  if (exception_state.is_exception_set()) {
    return false;
  }

  StaticPropertiesInterface::StaticFunction(arg1, arg2, arg3);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool staticfcn_staticFunction(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  switch(argc) {
    case(0): {
      // Overload resolution algorithm details found here:
      //     http://heycam.github.io/webidl/#dfn-overload-resolution-algorithm
      if (true) {
        return staticfcn_staticFunction1(
                  context, argc, vp);
      }
      break;
    }
    case(1): {
      // Overload resolution algorithm details found here:
      //     http://heycam.github.io/webidl/#dfn-overload-resolution-algorithm
      JS::RootedValue arg(context, args[0]);
      MozjsGlobalObjectProxy* global_object_proxy =
          static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
      WrapperFactory* wrapper_factory = global_object_proxy->wrapper_factory();
      if (arg.isNumber()) {
        return staticfcn_staticFunction2(
                  context, argc, vp);
      }
      if (true) {
        return staticfcn_staticFunction3(
                  context, argc, vp);
      }
      if (true) {
        return staticfcn_staticFunction2(
                  context, argc, vp);
      }
      break;
    }
    case(3): {
      // Overload resolution algorithm details found here:
      //     http://heycam.github.io/webidl/#dfn-overload-resolution-algorithm
      JS::RootedValue arg(context, args[2]);
      MozjsGlobalObjectProxy* global_object_proxy =
          static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
      WrapperFactory* wrapper_factory = global_object_proxy->wrapper_factory();
      if (arg.isObject() ? wrapper_factory->DoesObjectImplementInterface(
              JSVAL_TO_OBJECT(arg), base::GetTypeId<ArbitraryInterface>()) :
              false) {
        return staticfcn_staticFunction5(
                  context, argc, vp);
      }
      if (true) {
        return staticfcn_staticFunction4(
                  context, argc, vp);
      }
      break;
    }
  }
  // Invalid number of args
  // http://heycam.github.io/webidl/#dfn-overload-resolution-algorithm
  // 4. If S is empty, then throw a TypeError.
  MozjsExceptionState exception_state(context);
  exception_state.SetSimpleException(
      script::ExceptionState::kTypeError, "Invalid number of arguments.");
  return false;
}


const JSPropertySpec prototype_properties[] = {
  JS_PS_END
};

const JSFunctionSpec prototype_functions[] = {
  JS_FS_END
};

const JSPropertySpec interface_object_properties[] = {
  {  // Static read/write attribute.
      "staticAttribute", 0,
      JSPROP_SHARED | JSPROP_ENUMERATE,
      JSOP_WRAPPER(&staticget_staticAttribute),
      JSOP_WRAPPER(&staticset_staticAttribute),
  },
  JS_PS_END
};

const JSFunctionSpec interface_object_functions[] = {
  {
      "staticFunction",
      JSOP_WRAPPER(&staticfcn_staticFunction),
      0,
      JSPROP_ENUMERATE,
      NULL,
  },
  JS_FS_END
};

const JSPropertySpec own_properties[] = {
  JS_PS_END
};

void InitializePrototypeAndInterfaceObject(
    InterfaceData* interface_data, JSContext* context,
    JS::HandleObject global_object) {
  DCHECK(!interface_data->prototype);
  DCHECK(!interface_data->interface_object);
  DCHECK(JS_IsGlobalObject(global_object));

  JS::RootedObject parent_prototype(
      context, JS_GetObjectPrototype(context, global_object));
  DCHECK(parent_prototype);

  // Create the Prototype object.
  interface_data->prototype = JS_NewObjectWithGivenProto(
      context, &interface_data->prototype_class_definition, parent_prototype,
      NULL);
  bool success = JS_DefineProperties(
      context, interface_data->prototype, prototype_properties);
  DCHECK(success);
  success = JS_DefineFunctions(
      context, interface_data->prototype, prototype_functions);
  DCHECK(success);

  JS::RootedObject function_prototype(
      context, JS_GetFunctionPrototype(context, global_object));
  DCHECK(function_prototype);
  // Create the Interface object.
  interface_data->interface_object = JS_NewObjectWithGivenProto(
      context, &interface_data->interface_object_class_definition,
      function_prototype, NULL);

  // Add the InterfaceObject.name property.
  JS::RootedObject rooted_interface_object(
      context, interface_data->interface_object);
  JS::RootedValue name_value(context);
  const char name[] =
      "StaticPropertiesInterface";
  name_value.setString(JS_NewStringCopyZ(context, name));
  success =
      JS_DefineProperty(context, rooted_interface_object, "name", name_value,
                        JS_PropertyStub, JS_StrictPropertyStub,
                        JSPROP_READONLY);
  DCHECK(success);

  // Define interface object properties (including constants).
  success = JS_DefineProperties(context, rooted_interface_object,
                                interface_object_properties);
  DCHECK(success);
  // Define interface object functions (static).
  success = JS_DefineFunctions(context, rooted_interface_object,
                               interface_object_functions);
  DCHECK(success);


  // Set the Prototype.constructor and Constructor.prototype properties.
  DCHECK(interface_data->interface_object);
  DCHECK(interface_data->prototype);
  JS::RootedObject rooted_prototype(context, interface_data->prototype);
  success = JS_LinkConstructorAndPrototype(
      context,
      rooted_interface_object,
      rooted_prototype);
  DCHECK(success);
}

InterfaceData* GetInterfaceData(JSContext* context) {
  MozjsGlobalObjectProxy* global_object_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
  // Use the address of the properties definition for this interface as a
  // unique key for looking up the InterfaceData for this interface.
  intptr_t key = reinterpret_cast<intptr_t>(&own_properties);
  InterfaceData* interface_data = global_object_proxy->GetInterfaceData(key);
  if (!interface_data) {
    interface_data = CreateCachedInterfaceData();
    DCHECK(interface_data);
    global_object_proxy->CacheInterfaceData(key, interface_data);
    DCHECK_EQ(interface_data, global_object_proxy->GetInterfaceData(key));
  }
  return interface_data;
}

}  // namespace

// static
JSObject* MozjsStaticPropertiesInterface::CreateProxy(
    JSContext* context, const scoped_refptr<Wrappable>& wrappable) {
  JS::RootedObject global_object(context, JS_GetGlobalForScopeChain(context));
  DCHECK(global_object);

  InterfaceData* interface_data = GetInterfaceData(context);
  JS::RootedObject prototype(context, GetPrototype(context, global_object));
  DCHECK(prototype);
  JS::RootedObject new_object(context, JS_NewObjectWithGivenProto(
      context, &interface_data->instance_class_definition, prototype, NULL));
  DCHECK(new_object);
  JS::RootedObject proxy(context,
      ProxyHandler::NewProxy(context, new_object, prototype, NULL,
                             proxy_handler.Pointer()));
  WrapperPrivate::AddPrivateData(context, proxy, wrappable);
  return proxy;
}

//static
const JSClass* MozjsStaticPropertiesInterface::PrototypeClass(
      JSContext* context) {
  JS::RootedObject global_object(context, JS_GetGlobalForScopeChain(context));
  DCHECK(global_object);

  JS::RootedObject prototype(context, GetPrototype(context, global_object));
  JSClass* proto_class = JS_GetClass(*prototype.address());
  return proto_class;
}

// static
JSObject* MozjsStaticPropertiesInterface::GetPrototype(
    JSContext* context, JS::HandleObject global_object) {
  DCHECK(JS_IsGlobalObject(global_object));

  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->prototype) {
    // Create new prototype that has all the props and methods
    InitializePrototypeAndInterfaceObject(
        interface_data, context, global_object);
  }
  DCHECK(interface_data->prototype);
  return interface_data->prototype;
}

// static
JSObject* MozjsStaticPropertiesInterface::GetInterfaceObject(
    JSContext* context, JS::HandleObject global_object) {
  DCHECK(JS_IsGlobalObject(global_object));

  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->interface_object) {
    InitializePrototypeAndInterfaceObject(
        interface_data, context, global_object);
  }
  DCHECK(interface_data->interface_object);
  return interface_data->interface_object;
}


namespace {
}  // namespace


}  // namespace testing
}  // namespace bindings
}  // namespace cobalt
