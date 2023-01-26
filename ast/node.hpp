#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

#include <iostream>

class INode {
 public:
  virtual ~INode() = 0;

  virtual void PrintNode(std::ostream &os) const = 0;
};

#endif  // PARSER_NODE_HPP
