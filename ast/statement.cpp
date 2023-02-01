#include "statement.hpp"

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

std::shared_ptr<IStatement> LetStmt::Clone() const {
  return std::make_shared<LetStmt>(*this);
}

//===----------------------------------------------------------------------===//
// ReturnStmt
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(ReturnStmt, {
  os << tok_->literal << " ";
  value_->PrintNode(os);
  os << ";";
})

void ReturnStmt::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IStatement> ReturnStmt::Clone() const {
  return std::make_shared<ReturnStmt>(*this);
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

std::shared_ptr<IStatement> ExpressionStmt::Clone() const {
  return std::make_shared<ExpressionStmt>(*this);
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

std::shared_ptr<IStatement> BlockStmt::Clone() const {
  return std::make_shared<BlockStmt>(*this);
}
