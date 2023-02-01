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

  virtual std::shared_ptr<Derived> Clone() const;
};

template<typename Derived>
ClonableNode<Derived>::~ClonableNode() {}

template<typename Derived>
std::shared_ptr<Derived> ClonableNode<Derived>::Clone() const {
  return nullptr;
}

#endif  // PARSER_NODE_HPP
