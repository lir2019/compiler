#include "node.hpp"

std::string Identifier::TokenLiteral() {
  return tok_.literal;
}

void Identifier::ExpressionNode() {
}

std::string LetStmt::TokenLiteral() {
  return tok_.literal;
}

void LetStmt::StatementNode() {
}

std::string LetStmt::GetIdent() {
  return ident_->TokenLiteral();
}
