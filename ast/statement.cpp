#include "statement.hpp"

IStatement::~IStatement() {}

//===----------------------------------------------------------------------===//
// LetStmt
//===----------------------------------------------------------------------===//

LetStmt::~LetStmt() {}

DEFINE_DUMP_FUNCS(LetStmt, {
  os << tok_->literal << " " << *ident_ << " = ";
  value_->PrintNode(os);
  os << ";";
})

void LetStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// ReturnStmt
//===----------------------------------------------------------------------===//

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

DEFINE_DUMP_FUNCS(ExpressionStmt, {
  expression_->PrintNode(os);
  os << ";";
})

void ExpressionStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

//===----------------------------------------------------------------------===//
// BlockStmt
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(BlockStmt, {
  os << "{\n";
  for (auto stmt : stmts_) {
    stmt->PrintNode(os);
    os << "\n";
  }
  os << "}";
})

void BlockStmt::PrintNode(std::ostream &os) const {
  Print(os);
}
