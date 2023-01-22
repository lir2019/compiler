#ifndef OBJECT_OBJECT_HPP
#define OBJECT_OBJECT_HPP

#include <string>

enum class ObjectType {
  INT,
  BOOL,
  NUL,
};

class IObject {
 public:
  virtual ~IObject() {}

  virtual ObjectType Type() const = 0;
  virtual std::string Inspect() const = 0;
};

class Integer : public IObject {
 public:
  virtual ~Integer() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;
 private:
  int64_t value_;
};

class Boolean : public IObject {
 public:
  virtual ~Boolean() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;
 private:
  bool value_;
};

class Null : public IObject {
 public:
  virtual ~Null() {}

  virtual ObjectType Type() const override;
  virtual std::string Inspect() const override;
};

#endif  // OBJECT_OBJECT_HPP
