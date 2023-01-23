#include "object.hpp"

//===----------------------------------------------------------------------===//
// Integer
//===----------------------------------------------------------------------===//

ObjectType Integer::Type() const {
  return ObjectType::INT;
}

std::string Integer::Inspect() const {
  return std::to_string(value_);
}

//===----------------------------------------------------------------------===//
// Boolean
//===----------------------------------------------------------------------===//

ObjectType Boolean::Type() const {
  return ObjectType::BOOL;
}

std::string Boolean::Inspect() const {
  return value_ ? "true" : "false";
}

//===----------------------------------------------------------------------===//
// Null
//===----------------------------------------------------------------------===//

ObjectType Null::Type() const {
  return ObjectType::NUL;
}

std::string Null::Inspect() const {
  return "null";
}

//===----------------------------------------------------------------------===//
// ReturnValue
//===----------------------------------------------------------------------===//

ObjectType ReturnValue::Type() const {
  return ObjectType::RET;
}

std::string ReturnValue::Inspect() const {
  return value_->Inspect();
}

//===----------------------------------------------------------------------===//
// Error
//===----------------------------------------------------------------------===//

ObjectType Error::Type() const {
  return ObjectType::ERR;
}

std::string Error::Inspect() const {
  return "ERROR: " + message_;
}
