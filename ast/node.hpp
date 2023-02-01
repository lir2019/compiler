#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

#include <iostream>
#include <memory>

class INode {
 public:
  virtual ~INode() = 0;

  virtual void PrintNode(std::ostream &os) const = 0;
};

template<typename Derived>
class ClonableNode : public INode {
 public:
  virtual ~ClonableNode();

  virtual std::shared_ptr<Derived> Clone() const = 0;
};

template<typename Derived>
ClonableNode<Derived>::~ClonableNode() {}

class IExpression : public ClonableNode<IExpression> {
 public:
  virtual ~IExpression() = 0;
};

class IStatement : public ClonableNode<IStatement> {
 public:
  virtual ~IStatement() = 0;
};

#endif  // PARSER_NODE_HPP
