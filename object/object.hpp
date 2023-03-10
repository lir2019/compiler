#ifndef OBJECT_OBJECT_HPP
#define OBJECT_OBJECT_HPP

#include <string>
#include <map>
#include <iostream>
#include <functional>

#include "../common/utils.hpp"
#include "../ast/program.hpp"

enum class ObjectType {
  INT,
  BOOL,
  STRING,
  NUL,
  RET,
  ERR,
  FUNC,
  BUILTIN,
};

class IObject {
 public:
  virtual ~IObject() {}

  virtual ObjectType Type() const     = 0;
  virtual std::string Inspect() const = 0;
};

class Environment {
 public:
  Environment(std::shared_ptr<Environment> outer = nullptr) : outer_(outer) {}
  ~Environment() {}

  const std::shared_ptr<IObject> Get(const std::string &name) const;
  void Set(const std::string &name, std::shared_ptr<IObject> obj);
  void Print(std::ostream &os);

 private:
  std::map<std::string, std::shared_ptr<IObject>> store_;
  std::shared_ptr<Environment> outer_;
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

class String : public IObject {
 public:
  String(const std::string &value) : value_(value) {}
  virtual ~String() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

  std::string GetValue() const { return value_; }

 private:
  std::string value_;
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

class Function : public IObject {
 public:
  Function(std::vector<Identifier> parameters,
           std::shared_ptr<IStatement> body,
           std::shared_ptr<Environment> env)
      : parameters_(parameters), body_(body), env_(env) {}
  virtual ~Function() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

  void Set(const std::string &name, std::shared_ptr<IObject> obj) {
    env_->Set(name, obj);
  }

  std::vector<Identifier> GetParams() const { return parameters_; }
  std::shared_ptr<IStatement> GetBody() const { return body_; }
  std::shared_ptr<Environment> GetEnv() const { return env_; }

 private:
  std::vector<Identifier> parameters_;
  std::shared_ptr<IStatement> body_;
  std::shared_ptr<Environment> env_;
};

class Builtin : public IObject {
 public:
  using BuiltinFunction = std::function<std::shared_ptr<IObject>(std::vector<std::shared_ptr<IObject>>)>;

  Builtin(BuiltinFunction func) : func_(func) {}
  virtual ~Builtin() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;

 private:
  BuiltinFunction func_;
};

#ifndef RETURN_IF_ERROR
#define RETURN_IF_ERROR(OBJ)                   \
  if (std::dynamic_pointer_cast<Error>(OBJ)) { \
    return OBJ;                                \
  }
#endif

#endif  // OBJECT_OBJECT_HPP
