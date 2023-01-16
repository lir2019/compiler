#include <iostream>

#include "node.hpp"

std::string Identifier::TokenLiteral() const {
  return tok_.literal;
}

void Identifier::ExpressionNode() {
}

DEFINE_DUMP_FUNCS(Identifier, { os << "Identifier(" << tok_ << ")"; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}

std::string LetStmt::TokenLiteral() const {
  return tok_.literal;
}

void LetStmt::StatementNode() {
}

DEFINE_DUMP_FUNCS(LetStmt, { os << "LetStmt(" << tok_ << ", " << *ident_ << ")"; })

void LetStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

std::string LetStmt::GetIdent() {
  return ident_->TokenLiteral();
}
