#include "statement.hpp"

IStatement::~IStatement() {}

//===----------------------------------------------------------------------===//
// LetStmt
//===----------------------------------------------------------------------===//

LetStmt::~LetStmt() {}

std::string LetStmt::TokenLiteral() const {
  return tok_.literal;
}

void LetStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(LetStmt, {
  os << tok_.literal << " " << *ident_ << " = ";
  value_->PrintNode(os);
  os << ";";
})

void LetStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

std::string LetStmt::GetIdent() {
  return ident_->TokenLiteral();
}

//===----------------------------------------------------------------------===//
// ReturnStmt
//===----------------------------------------------------------------------===//

ReturnStmt::~ReturnStmt() {}

std::string ReturnStmt::TokenLiteral() const {
  return tok_.literal;
}

void ReturnStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(ReturnStmt, {
  os << tok_.literal << " ";
  value_->PrintNode(os);
  os << ";";
})

void ReturnStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// ExpressionStmt
//===----------------------------------------------------------------------===//

ExpressionStmt::~ExpressionStmt() {}

void ExpressionStmt::StatementNode() const {}

DEFINE_DUMP_FUNCS(ExpressionStmt, {
  expression_->PrintNode(os);
  os << ";";
})

std::string ExpressionStmt::TokenLiteral() const {
  return tok_.literal;
}

void ExpressionStmt::PrintNode(std::ostream &os) const {
  Print(os);
}
