#include <iostream>

#include "node.hpp"

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() {
}

void Identifier::Print(std::ostream &os) const {
  os << "Identifier(" << tok_ << ")";
}

std::ostream &operator<<(std::ostream &os, const Identifier &ident) {
  ident.Print(os);
  return os;
}

std::string LetStmt::TokenLiteral() const {
  return tok_.literal;
}

void LetStmt::StatementNode() {
}

void LetStmt::Print(std::ostream &os) const {
  os << "LetStmt(" << tok_ << ", " << *ident_ << ")";
}

std::ostream &operator<<(std::ostream &os, const LetStmt &let_stmt) {
  let_stmt.Print(os);
  return os;
}

std::string LetStmt::GetIdent() {
  return ident_->TokenLiteral();
}
