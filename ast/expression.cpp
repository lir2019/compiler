#include "expression.hpp"

#include <iostream>

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(Identifier, { os << "Identifier(" << tok_ << ")"; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}
