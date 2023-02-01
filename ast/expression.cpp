#include "expression.hpp"

#include <iostream>

#include "statement.hpp"

//===----------------------------------------------------------------------===//
// Identifier
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(Identifier, { os << tok_->literal; })

void Identifier::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> Identifier::Clone() const {
  return std::make_shared<Identifier>(*this);
}

//===----------------------------------------------------------------------===//
// IntegerLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(IntegerLiteral, { os << tok_->literal; })

void IntegerLiteral::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> IntegerLiteral::Clone() const {
  return std::make_shared<IntegerLiteral>(*this);
}

//===----------------------------------------------------------------------===//
// BooleanLiteral
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(BooleanLiteral, { os << tok_->literal; })

void BooleanLiteral::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> BooleanLiteral::Clone() const {
  return std::make_shared<BooleanLiteral>(*this);
}

//===----------------------------------------------------------------------===//
// PrefixExpression
//===----------------------------------------------------------------------===//

DEFINE_DUMP_FUNCS(PrefixExpression, {
  os << "(" << tok_->literal;
  right_->PrintNode(os);
  os << ")";
})

void PrefixExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> PrefixExpression::Clone() const {
  return std::make_shared<PrefixExpression>(*this);
}

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

void InfixExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> InfixExpression::Clone() const {
  return std::make_shared<InfixExpression>(*this);
}

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

void IfExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> IfExpression::Clone() const {
  return std::make_shared<IfExpression>(*this);
}

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

void FuncLiteral::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> FuncLiteral::Clone() const {
  return std::make_shared<FuncLiteral>(*this);
}

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

void CallExpression::PrintNode(std::ostream &os) const {
  Print(os);
}

std::shared_ptr<IExpression> CallExpression::Clone() const {
  return std::make_shared<CallExpression>(*this);
}
