#ifndef OBJECT_OBJECT_HPP
#define OBJECT_OBJECT_HPP

#include <string>

enum class ObjectType {
  INT,
  BOOL,
  NUL,
  RET,
};

class IObject {
 public:
  virtual ~IObject() {}

  virtual ObjectType Type() const = 0;
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

#endif  // OBJECT_OBJECT_HPP
