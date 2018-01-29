/*
 * Copyright 2018 Google Inc. All Rights Reserved.
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

// clang-format off

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/mozjs45/templates/enumeration-conversion.cc.template

#include "cobalt/bindings/testing/test_enum.h"

#include "mozjs_gen_type_conversion.h"
#include "cobalt/script/exception_state.h"
#include "third_party/mozjs-45/js/src/jsapi.h"

using cobalt::bindings::testing::TestEnum;

namespace cobalt {
namespace script {
namespace mozjs {

void ToJSValue(
    JSContext* context,
    TestEnum in_enum,
    JS::MutableHandleValue out_value) {
  switch (in_enum) {
    case cobalt::bindings::testing::kTestEnumAlpha:
      ToJSValue(context, std::string("alpha"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumBeta:
      ToJSValue(context, std::string("beta"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumGamma:
      ToJSValue(context, std::string("gamma"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumEnumWithDashes:
      ToJSValue(context, std::string("enum-with-dashes"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumEnumWithSpaces:
      ToJSValue(context, std::string("enum with spaces"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumTerribleEnum:
      ToJSValue(context, std::string("terrible----enum"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumThisIsATerribleEnum:
      ToJSValue(context, std::string("this is a terrible @#$%#$% enum"), out_value);
      return;
    default:
      NOTREACHED();
      out_value.set(JS::UndefinedValue());
  }
}

void FromJSValue(JSContext* context, JS::HandleValue value,
                 int conversion_flags, ExceptionState* exception_state,
                 TestEnum* out_enum) {
  DCHECK_EQ(0, conversion_flags) << "Unexpected conversion flags.";
  // JSValue -> IDL enum algorithm described here:
  // http://heycam.github.io/webidl/#es-enumeration
  // 1. Let S be the result of calling ToString(V).
  JS::RootedString rooted_string(context, JS::ToString(context, value));

  bool match = false;
// 3. Return the enumeration value of type E that is equal to S.
if (JS_StringEqualsAscii(
      context, rooted_string, "alpha", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumAlpha;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "beta", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumBeta;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "gamma", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumGamma;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "enum-with-dashes", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumEnumWithDashes;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "enum with spaces", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumEnumWithSpaces;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "terrible----enum", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumTerribleEnum;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "this is a terrible @#$%#$% enum", &match)
      && match) {
    *out_enum = cobalt::bindings::testing::kTestEnumThisIsATerribleEnum;
  } else {
    // 2. If S is not one of E's enumeration values, then throw a TypeError.
    exception_state->SetSimpleException(cobalt::script::kConvertToEnumFailed);
    return;
  }
}

}  // namespace mozjs
}  // namespace script
}  // namespace cobalt
