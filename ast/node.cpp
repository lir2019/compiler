#include <iostream>

#include "node.hpp"

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() const {}

DEFINE_DUMP_FUNCS(Identifier, { os << "Identifier(" << tok_ << ")"; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}

std::string LetStmt::TokenLiteral() const {
  return tok_.literal;
}

void LetStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(LetStmt, { os << "LetStmt(" << tok_ << ", " << *ident_ << ")"; })

void LetStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

std::string LetStmt::GetIdent() {
  return ident_->TokenLiteral();
}

std::string ReturnStmt::TokenLiteral() const {
  return tok_.literal;
}

void ReturnStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(ReturnStmt, { os << "ReturnStmt(" << tok_ << ")"; })

void ReturnStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

void ExpressionStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(ExpressionStmt, {
  os << "ExpressionStmt(" << tok_ << ", ";
  expression_->PrintNode(os);
  os << ")";
})

std::string ExpressionStmt::TokenLiteral() const {
  return tok_.literal;
}

void ExpressionStmt::PrintNode(std::ostream &os) const {
  Print(os);
}
