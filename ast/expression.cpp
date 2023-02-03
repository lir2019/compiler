#include "expression.hpp"

#include <iostream>

#include "statement.hpp"

//===----------------------------------------------------------------------===//
// Identifier
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(Identifier, { os << tok_->literal; })

//===----------------------------------------------------------------------===//
// IntegerLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(IntegerLiteral, { os << tok_->literal; })

//===----------------------------------------------------------------------===//
// BooleanLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(BooleanLiteral, { os << tok_->literal; })

//===----------------------------------------------------------------------===//
// StringLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(StringLiteral, { os << "\"" + tok_->literal + "\""; })

//===----------------------------------------------------------------------===//
// PrefixExpression
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(PrefixExpression, {
  os << "(" << tok_->literal;
  right_->PrintNode(os);
  os << ")";
})

//===----------------------------------------------------------------------===//
// InfixExpression
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(InfixExpression, {
  os << "(";
  left_->PrintNode(os);
  os << " " << tok_->literal << " ";
  right_->PrintNode(os);
  os << ")";
})

//===----------------------------------------------------------------------===//
// IfExpression
//===----------------------------------------------------------------------===//

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

//===----------------------------------------------------------------------===//
// FuncLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(FuncLiteral, {
  os << "fn(";
  for (int i = 0; i < (int)parameters_.size() - 1; i++) {
    parameters_[i].Print(os);
    os << ", ";
  }
  if (!parameters_.empty()) {
    parameters_.back().Print(os);
  }
  os << ") ";
  body_->PrintNode(os);
})

//===----------------------------------------------------------------------===//
// CallExpression
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(CallExpression, {
  func_->PrintNode(os);
  os << "(";
  for (int i = 0; i < (int)arguments_.size() - 1; i++) {
    arguments_[i]->PrintNode(os);
    os << ", ";
  }
  if (!arguments_.empty()) {
    arguments_.back()->PrintNode(os);
  }
  os << ")";
})
