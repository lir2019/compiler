#include "expression.hpp"

#include <iostream>

//===----------------------------------------------------------------------===//
// Identifier
//===----------------------------------------------------------------------===//

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(Identifier, { os << "Identifier(" << tok_ << ")"; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// IntegerLiteral
//===----------------------------------------------------------------------===//

std::string IntegerLiteral::TokenLiteral() const {
  return tok_.literal;
}

void IntegerLiteral::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(IntegerLiteral, { os << "IntegerLiteral(" << tok_ << ")"; })

void IntegerLiteral::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// PrefixExpression
//===----------------------------------------------------------------------===//

std::string PrefixExpression::TokenLiteral() const {
  return tok_.literal;
}

void PrefixExpression::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(PrefixExpression, {
  os << "PrefixExpression(" << tok_ << ", ";
  right_->PrintNode(os);
  os << ")";
})

void PrefixExpression::PrintNode(std::ostream &os) const {
  Print(os);
}
