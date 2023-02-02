#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

#include <iostream>
#include <memory>

class INode {
 public:
  virtual ~INode() = 0;

  virtual void PrintNode(std::ostream &os) const = 0;
};

template <typename Derived>
class ClonableNode : public INode {
 public:
  virtual ~ClonableNode();

  virtual std::shared_ptr<Derived> Clone() const = 0;
};

template <typename Derived>
ClonableNode<Derived>::~ClonableNode() {}

class IExpression : public ClonableNode<IExpression> {
 public:
  virtual ~IExpression() = 0;
};

class IStatement : public ClonableNode<IStatement> {
 public:
  virtual ~IStatement() = 0;
};

template <typename ConCreteExp>
class Expression : public IExpression {
 public:
  virtual ~Expression(){};

  virtual std::shared_ptr<IExpression> Clone() const override {
    return std::make_shared<ConCreteExp>(
        static_cast<const ConCreteExp &>(*this));
  }

  virtual void PrintNode(std::ostream &os) const override {
    static_cast<const ConCreteExp &>(*this).Print(os);
  }
};

template <typename ConCreteStmt>
class Statement : public IStatement {
 public:
  virtual ~Statement(){};

  virtual std::shared_ptr<IStatement> Clone() const override {
    return std::make_shared<ConCreteStmt>(
        static_cast<const ConCreteStmt &>(*this));
  }

  virtual void PrintNode(std::ostream &os) const override {
    static_cast<const ConCreteStmt &>(*this).Print(os);
  }
};

#endif  // PARSER_NODE_HPP
