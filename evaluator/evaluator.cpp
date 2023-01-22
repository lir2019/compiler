#include "evaluator.hpp"

#include "../ast/program.hpp"

static std::shared_ptr<IObject> EvalPrefixExpression(Token op, std::shared_ptr<IObject> right) {
  switch (op.type) {
    case TokenType::BANG: {
        auto boolean = std::dynamic_pointer_cast<Boolean>(right);
        CHECK(boolean != nullptr, "expect Boolean");
        return std::make_shared<Boolean>(!boolean->GetValue());
    } break;
    case TokenType::MINUS: {
        auto integer = std::dynamic_pointer_cast<Integer>(right);
        CHECK(integer != nullptr, "expect Integer");
        return std::make_shared<Integer>(-integer->GetValue());
    } break;
    default: return nullptr;
  }
}

std::shared_ptr<IObject> Eval(const INode &node) {
  if (auto program = dynamic_cast<const Program *>(&node)) {
    return nullptr;
  } else if (auto exp_stmt = dynamic_cast<const ExpressionStmt *>(&node)) {
    return nullptr;
  } else if (auto int_lit = dynamic_cast<const IntegerLiteral *>(&node)) {
    return std::make_shared<Integer>(int_lit->GetValue());
  } else if (auto bool_lit = dynamic_cast<const BooleanLiteral *>(&node)) {
    return std::make_shared<Boolean>(bool_lit->GetValue());
  } else if (auto prefix_exp = dynamic_cast<const PrefixExpression *>(&node)) {
    auto right = Eval(*(prefix_exp->GetRight()));
    return EvalPrefixExpression(prefix_exp->GetOperator(), right);
  }
  return nullptr;
}
