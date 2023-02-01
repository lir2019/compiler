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

std::shared_ptr<IStatement> LetStmt::Clone() const {
  return std::make_shared<LetStmt>(*tok_, *ident_, value_);
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
  return std::make_shared<ReturnStmt>(*tok_, value_);
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
  return std::make_shared<ExpressionStmt>(*tok_, expression_);
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
  auto block = std::make_shared<BlockStmt>(*tok_);
  for (auto stmt : stmts_) {
    block->AppendStmt(stmt);
  }
  return block;
}
