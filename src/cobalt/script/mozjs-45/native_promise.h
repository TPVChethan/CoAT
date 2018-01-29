// Copyright 2017 Google Inc. All Rights Reserved.
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

#ifndef COBALT_SCRIPT_MOZJS_45_NATIVE_PROMISE_H_
#define COBALT_SCRIPT_MOZJS_45_NATIVE_PROMISE_H_

#include "cobalt/script/mozjs-45/conversion_helpers.h"
#include "cobalt/script/mozjs-45/mozjs_exception_state.h"
#include "cobalt/script/mozjs-45/mozjs_user_object_holder.h"
#include "cobalt/script/mozjs-45/promise_wrapper.h"
#include "cobalt/script/mozjs-45/type_traits.h"
#include "cobalt/script/mozjs-45/weak_heap_object.h"
#include "cobalt/script/promise.h"
#include "third_party/mozjs-45/js/src/jsapi.h"

namespace cobalt {
namespace script {
namespace mozjs {

// TODO: This lives here instead of conversion_helpers.h because right now
// |PromiseResultUndefined| is specific to promises.  In the long run, we plan
// on abstracting all JavaScript value types, and should just use however that
// abstraction exposes "undefined" here instead.
inline void ToJSValue(JSContext* context,
                      const PromiseResultUndefined& in_undefined,
                      JS::MutableHandleValue out_value) {
  out_value.setUndefined();
}

// Shared functionality for NativePromise<T>. Does not implement the Resolve
// function, since that needs to be specialized for Promise<T>.
template <typename T>
class NativePromise : public Promise<T> {
 public:
  // ScriptObject boilerplate.
  typedef Promise<T> BaseType;

  // Handle special case T=void, by swapping the input parameter |T| for
  // |PromiseResultUndefined|. Combined with how |Promise| handles this
  // special case, we're left with something like:
  //
  //   NativePromise<T>    ->            Promise<T>
  //                                         ^
  //                                         | (T=PromiseResultUndefined)
  //                                        /
  //   NativePromise<void> -> Promise<void>
  //
  using ResolveType =
      typename std::conditional<std::is_same<T, void>::value,
                                PromiseResultUndefined, T>::type;

  NativePromise(JSContext* context, JS::HandleValue resolver_value)
      : context_(context) {
    DCHECK(resolver_value.isObject());
    promise_resolver_.emplace(context, resolver_value);
  }

  JSObject* handle() const { return promise_resolver_->get().GetObject(); }
  const JS::Value& value() const { return promise_resolver_->get().GetValue(); }
  bool WasCollected() const { return promise_resolver_->get().WasCollected(); }

  // The Promise JS object (not the resolver).
  JSObject* promise() const { return promise_resolver_->GetPromise(); }

  void Resolve(const ResolveType& value) const override {
    JS::RootedObject promise_wrapper(context_,
                                     promise_resolver_->get().GetObject());
    if (!promise_wrapper) {
      return;
    }
    JSAutoRequest auto_request(context_);
    JSAutoCompartment auto_compartment(context_, promise_wrapper);
    JS::RootedValue converted_value(context_);
    ToJSValue(context_, value, &converted_value);
    promise_resolver_->Resolve(converted_value);
  }

  void Reject() const override {
    JS::RootedObject promise_resolver(context_,
                                      promise_resolver_->get().GetObject());
    if (!promise_resolver) {
      return;
    }
    JSAutoRequest auto_request(context_);
    JSAutoCompartment auto_compartment(context_, promise_resolver);
    promise_resolver_->Reject(JS::UndefinedHandleValue);
  }

  void Reject(SimpleExceptionType exception) const override {
    JS::RootedObject promise_resolver(context_,
                                      promise_resolver_->get().GetObject());
    if (!promise_resolver) {
      return;
    }
    JSAutoRequest auto_request(context_);
    JSAutoCompartment auto_compartment(context_, promise_resolver);
    JS::RootedValue error_result(context_);
    error_result.setObject(
        *MozjsExceptionState::CreateErrorObject(context_, exception));
    promise_resolver_->Reject(error_result);
  }

  void Reject(const scoped_refptr<ScriptException>& result) const override {
    JS::RootedObject promise_resolver(context_,
                                      promise_resolver_->get().GetObject());
    if (!promise_resolver) {
      return;
    }
    JSAutoRequest auto_request(context_);
    JSAutoCompartment auto_compartment(context_, promise_resolver);
    JS::RootedValue converted_result(context_);
    ToJSValue(context_, result, &converted_result);
    promise_resolver_->Reject(converted_result);
  }

 private:
  JSContext* context_;
  base::optional<PromiseWrapper> promise_resolver_;
};

template <typename T>
struct TypeTraits<NativePromise<T>> {
  typedef MozjsUserObjectHolder<NativePromise<T>> ConversionType;
  typedef const ScriptValue<Promise<T>>* ReturnType;
};

// Promise<T> -> JSValue
// Note that JSValue -> Promise<T> is not yet supported.
template <typename T>
inline void ToJSValue(JSContext* context,
                      const ScriptValue<Promise<T>>* promise_holder,
                      JS::MutableHandleValue out_value) {
  TRACK_MEMORY_SCOPE("Javascript");
  if (!promise_holder) {
    out_value.set(JS::NullValue());
    return;
  }
  const MozjsUserObjectHolder<NativePromise<T>>* user_object_holder =
      base::polymorphic_downcast<
          const MozjsUserObjectHolder<NativePromise<T>>*>(promise_holder);

  const NativePromise<T>* native_promise =
      base::polymorphic_downcast<const NativePromise<T>*>(
          user_object_holder->GetScriptValue());

  DCHECK(native_promise);
  out_value.setObjectOrNull(native_promise->promise());
}

// Explicitly defer to the const version here so that a more generic non-const
// version of this function does not get called instead, in the case that
// |promise_holder| is not const.
template <typename T>
inline void ToJSValue(JSContext* context,
                      ScriptValue<Promise<T>>* promise_holder,
                      JS::MutableHandleValue out_value) {
  TRACK_MEMORY_SCOPE("Javascript");
  ToJSValue(context, const_cast<const ScriptValue<Promise<T>>*>(promise_holder),
            out_value);
}

// Destroys |promise_holder| as soon as the conversion is done.
// This is useful when a wrappable is not interested in retaining a reference
// to a promise, typically when a promise is resolved or rejected synchronously.
template <typename T>
inline void ToJSValue(JSContext* context,
                      scoped_ptr<ScriptValue<Promise<T>>> promise_holder,
                      JS::MutableHandleValue out_value) {
  ToJSValue(context, promise_holder.get(), out_value);
}

}  // namespace mozjs
}  // namespace script
}  // namespace cobalt
#endif  // COBALT_SCRIPT_MOZJS_45_NATIVE_PROMISE_H_
