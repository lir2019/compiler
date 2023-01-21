#include "expression.hpp"

#include <iostream>

#include "statement.hpp"

IExpression::~IExpression() {}

//===----------------------------------------------------------------------===//
// Identifier
//===----------------------------------------------------------------------===//

Identifier::~Identifier() {}

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(Identifier, { os << tok_.literal; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// IntegerLiteral
//===----------------------------------------------------------------------===//

IntegerLiteral::~IntegerLiteral() {}

std::string IntegerLiteral::TokenLiteral() const {
  return tok_.literal;
}

void IntegerLiteral::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(IntegerLiteral, { os << tok_.literal; })

void IntegerLiteral::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// Boolean
//===----------------------------------------------------------------------===//

Boolean::~Boolean() {}

std::string Boolean::TokenLiteral() const {
  return tok_.literal;
}

void Boolean::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(Boolean, { os << tok_.literal; })

void Boolean::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// PrefixExpression
//===----------------------------------------------------------------------===//

PrefixExpression::~PrefixExpression() {}

std::string PrefixExpression::TokenLiteral() const {
  return tok_.literal;
}

void PrefixExpression::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(PrefixExpression, {
  os << "(" << tok_.literal;
  right_->PrintNode(os);
  os << ")";
})

void PrefixExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// InfixExpression
//===----------------------------------------------------------------------===//

InfixExpression::~InfixExpression() {}

std::string InfixExpression::TokenLiteral() const {
  return tok_.literal;
}

void InfixExpression::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(InfixExpression, {
  os << "(";
  left_->PrintNode(os);
  os << " " << tok_.literal << " ";
  right_->PrintNode(os);
  os << ")";
})

void InfixExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// IfExpression
//===----------------------------------------------------------------------===//

std::string IfExpression::TokenLiteral() const {
  return tok_.literal;
}

void IfExpression::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(IfExpression, {
  os << "if ";
  cond_->PrintNode(os);
  os << " ";
  consequence_->PrintNode(os);
  if (alternative_) {
    os << " else ";
    alternative_->PrintNode(os);
  }
})

void IfExpression::PrintNode(std::ostream &os) const {
  Print(os);
}
