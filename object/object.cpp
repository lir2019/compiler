#include "object.hpp"

#include <sstream>

//===----------------------------------------------------------------------===//
// Environment
//===----------------------------------------------------------------------===//

const std::shared_ptr<IObject> Environment::Get(const std::string &name) const {
  // store_[name] will not compile!!!
  // because there is not a nonconst overload of operator[]
  bool exist = store_.find(name) != store_.end();
  if (exist) {
    return store_.at(name);
  } else {
    if (outer_) {
      return outer_->Get(name);
    } else {
      CHECK(false, name + " does not exist");
    }
  }
  return store_.at(name);
}
void Environment::Set(const std::string &name, std::shared_ptr<IObject> obj) {
  store_[name] = obj;
}

void Environment::Print(std::ostream &os) {
  os << "Environment{\n";
  for (auto e : store_) {
    os << "{" + e.first + ": " + e.second->Inspect() + "}\n";
  }
  os << "}\n";
}

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

//===----------------------------------------------------------------------===//
// Function
//===----------------------------------------------------------------------===//

ObjectType Function::Type() const {
  return ObjectType::FUNC;
}

std::string Function::Inspect() const {
  std::string ret("fn(");
  for (int i = 0; i < (int)parameters_.size() - 1; i++) {
    ret += parameters_[i].ToString() + ", ";
  }
  if (!parameters_.empty()) {
    ret += parameters_.back().ToString();
  }
  ret += ") ";
  std::stringstream ss;
  body_->PrintNode(ss);
  ret += ss.str();
  return ret;
}
