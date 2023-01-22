#include "evaluator.hpp"

#include "../ast/program.hpp"

std::shared_ptr<IObject> Eval(const INode &node) {
  if (auto program = dynamic_cast<const Program *>(&node)) {
    return nullptr;
  } else if (auto exp_stmt = dynamic_cast<const ExpressionStmt *>(&node)) {
    return nullptr;
  } else if (auto int_lit = dynamic_cast<const IntegerLiteral *>(&node)) {
    return std::make_shared<Integer>(int_lit->GetValue());
  } else if (auto bool_lit = dynamic_cast<const BooleanLiteral *>(&node)) {
    return std::make_shared<Boolean>(bool_lit->GetValue());
  }
  return nullptr;
}
