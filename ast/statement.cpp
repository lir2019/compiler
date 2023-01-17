#include "statement.hpp"

//===----------------------------------------------------------------------===//
// LetStmt
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
// ReturnStmt
//===----------------------------------------------------------------------===//

std::string ReturnStmt::TokenLiteral() const {
  return tok_.literal;
}

void ReturnStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(ReturnStmt, { os << "ReturnStmt(" << tok_ << ")"; })

void ReturnStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// ExpressionStmt
//===----------------------------------------------------------------------===//

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
