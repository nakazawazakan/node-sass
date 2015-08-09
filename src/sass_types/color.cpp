#include <nan.h>
#include "color.h"

namespace SassTypes
{
  Color::Color(Sass_Value* v) : SassValueWrapper(v) {}

  Sass_Value* Color::construct(const std::vector<v8::Local<v8::Value>> raw_val) {
    double a = 1.0, r = 0, g = 0, b = 0;
    unsigned argb;

    switch (raw_val.size()) {
    case 1:
      if (!raw_val[0]->IsNumber()) {
        throw std::invalid_argument("Only argument should be an integer.");
      }

      argb = raw_val[0]->ToInt32()->Value();
      a = (double)((argb >> 030) & 0xff) / 0xff;
      r = (double)((argb >> 020) & 0xff);
      g = (double)((argb >> 010) & 0xff);
      b = (double)(argb & 0xff);
      break;

    case 4:
      if (!raw_val[3]->IsNumber()) {
        throw std::invalid_argument("Constructor arguments should be numbers exclusively.");
      }

      a = raw_val[3]->ToNumber()->Value();
      // fall through vvv

    case 3:
      if (!raw_val[0]->IsNumber() || !raw_val[1]->IsNumber() || !raw_val[2]->IsNumber()) {
        throw std::invalid_argument("Constructor arguments should be numbers exclusively.");
      }

      r = raw_val[0]->ToNumber()->Value();
      g = raw_val[1]->ToNumber()->Value();
      b = raw_val[2]->ToNumber()->Value();
      break;

    case 0:
      break;

    default:
      throw std::invalid_argument("Constructor should be invoked with either 0, 1, 3 or 4 arguments.");
    }

    return sass_make_color(r, g, b, a);
  }

  void Color::initPrototype(v8::Local<v8::FunctionTemplate> proto) {
    Nan::SetPrototypeMethod(proto, "getR", GetR);
    Nan::SetPrototypeMethod(proto, "getG", GetG);
    Nan::SetPrototypeMethod(proto, "getB", GetB);
    Nan::SetPrototypeMethod(proto, "getA", GetA);
    Nan::SetPrototypeMethod(proto, "setR", SetR);
    Nan::SetPrototypeMethod(proto, "setG", SetG);
    Nan::SetPrototypeMethod(proto, "setB", SetB);
    Nan::SetPrototypeMethod(proto, "setA", SetA);
  }

  NAN_METHOD(Color::GetR) {
    info.GetReturnValue().Set(sass_color_get_r(unwrap(info.This())->value));
  }

  NAN_METHOD(Color::GetG) {
    info.GetReturnValue().Set(sass_color_get_g(unwrap(info.This())->value));
  }

  NAN_METHOD(Color::GetB) {
    info.GetReturnValue().Set(sass_color_get_b(unwrap(info.This())->value));
  }

  NAN_METHOD(Color::GetA) {
    info.GetReturnValue().Set(sass_color_get_a(unwrap(info.This())->value));
  }

  NAN_METHOD(Color::SetR) {
    if (info.Length() != 1) {
      return Nan::ThrowError(Nan::New("Expected just one argument").ToLocalChecked());
    }

    if (!info[0]->IsNumber()) {
      return Nan::ThrowError(Nan::New("Supplied value should be a number").ToLocalChecked());
    }

    sass_color_set_r(unwrap(info.This())->value, info[0]->ToNumber()->Value());
    return;
  }

  NAN_METHOD(Color::SetG) {
    if (info.Length() != 1) {
      return Nan::ThrowError(Nan::New("Expected just one argument").ToLocalChecked());
    }

    if (!info[0]->IsNumber()) {
      return Nan::ThrowError(Nan::New("Supplied value should be a number").ToLocalChecked());
    }

    sass_color_set_g(unwrap(info.This())->value, info[0]->ToNumber()->Value());
    return;
  }

  NAN_METHOD(Color::SetB) {
    if (info.Length() != 1) {
      return Nan::ThrowError(Nan::New("Expected just one argument").ToLocalChecked());
    }

    if (!info[0]->IsNumber()) {
      return Nan::ThrowError(Nan::New("Supplied value should be a number").ToLocalChecked());
    }

    sass_color_set_b(unwrap(info.This())->value, info[0]->ToNumber()->Value());
    return;
  }

  NAN_METHOD(Color::SetA) {
    if (info.Length() != 1) {
      return Nan::ThrowError(Nan::New("Expected just one argument").ToLocalChecked());
    }

    if (!info[0]->IsNumber()) {
      return Nan::ThrowError(Nan::New("Supplied value should be a number").ToLocalChecked());
    }

    sass_color_set_a(unwrap(info.This())->value, info[0]->ToNumber()->Value());
    return;
  }
}
