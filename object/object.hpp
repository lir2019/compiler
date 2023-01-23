#ifndef OBJECT_OBJECT_HPP
#define OBJECT_OBJECT_HPP

#include <string>
#include <map>
#include <iostream>

enum class ObjectType {
  INT,
  BOOL,
  NUL,
  RET,
  ERR,
};

class IObject {
 public:
  virtual ~IObject() {}

  virtual ObjectType Type() const     = 0;
  virtual std::string Inspect() const = 0;
};

class Integer : public IObject {
 public:
  Integer(int64_t value) : value_(value) {}
  virtual ~Integer() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

  int64_t GetValue() const { return value_; }

 private:
  int64_t value_;
};

class Boolean : public IObject {
 public:
  Boolean(bool value) : value_(value) {}
  virtual ~Boolean() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

  bool GetValue() const { return value_; }

 private:
  bool value_;
};

class Null : public IObject {
 public:
  virtual ~Null() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;
};

class ReturnValue : public IObject {
 public:
  ReturnValue(std::shared_ptr<IObject> value) : value_(value) {}
  virtual ~ReturnValue() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

  std::shared_ptr<IObject> GetValue() const { return value_; }

 private:
  std::shared_ptr<IObject> value_;
};

class Error : public IObject {
 public:
  Error(const std::string &m) : message_(m) {}
  virtual ~Error() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

 private:
  std::string message_;
};

#ifndef RETURN_IF_ERROR
#define RETURN_IF_ERROR(OBJ)                   \
  if (std::dynamic_pointer_cast<Error>(OBJ)) { \
    return OBJ;                                \
  }
#endif

class Environment {
 public:
  Environment() {}
  ~Environment() {}

  const std::shared_ptr<IObject> Get(const std::string &name) const {
    // store_[name] will not compile!!!
    // because there is not a nonconst overload of operator[]
    return store_.at(name);
  }
  void Set(const std::string &name, std::shared_ptr<IObject> obj) {
    store_[name] = obj;
  }

  void Print(std::ostream &os) {
    os << "Environment{\n";
    for (auto e : store_) {
      os << "{" + e.first + ": " + e.second->Inspect() + "}\n";
    }
    os << "}\n";
  }

 private:
  std::map<std::string, std::shared_ptr<IObject>> store_;
};

#endif  // OBJECT_OBJECT_HPP
