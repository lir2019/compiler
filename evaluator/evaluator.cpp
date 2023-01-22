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

#define CASE_INFIX_EVAL(TYPE, NAME, OP) \
    case TokenType::NAME: {     \
        return std::make_shared<TYPE>(left_val->GetValue() OP right_val->GetValue()); \
    } break;

static std::shared_ptr<IObject> EvalBoolInfixExpression(Token op, std::shared_ptr<IObject> left, std::shared_ptr<IObject> right) {
  auto left_val = std::dynamic_pointer_cast<Boolean>(left);
  auto right_val = std::dynamic_pointer_cast<Boolean>(right);
  CHECK(left_val != nullptr && right_val != nullptr, "expect both to be Boolean");
  switch (op.type) {
    CASE_INFIX_EVAL(Boolean, EQ, ==)
    CASE_INFIX_EVAL(Boolean, NE, !=)
    default: CHECK(false, "expect TokenType to be EQ or NE, but got " + op.ToString());
  }
  return nullptr;
}

static std::shared_ptr<IObject> EvalIntInfixExpression(Token op, std::shared_ptr<IObject> left, std::shared_ptr<IObject> right) {
  auto left_val = std::dynamic_pointer_cast<Integer>(left);
  auto right_val = std::dynamic_pointer_cast<Integer>(right);
  CHECK(left_val != nullptr && right_val != nullptr, "expect both to be Integer");
  switch (op.type) {
    CASE_INFIX_EVAL(Boolean, EQ, ==)
    CASE_INFIX_EVAL(Boolean, NE, !=)
    CASE_INFIX_EVAL(Boolean, GT, >)
    CASE_INFIX_EVAL(Boolean, LT, <)
    CASE_INFIX_EVAL(Integer, PLUS, +)
    CASE_INFIX_EVAL(Integer, MINUS, -)
    CASE_INFIX_EVAL(Integer, ASTERISK, *)
    CASE_INFIX_EVAL(Integer, SLASH, /)
    default: CHECK(false, "expect TokenType to be EQ or NE, but got " + op.ToString());
  }
  return nullptr;
}

#undef CASE_INT_INFIX_EVAL

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
  } else if (auto infix_exp = dynamic_cast<const InfixExpression *>(&node)) {
    auto left = Eval(*(infix_exp->GetLeft()));
    auto right = Eval(*(infix_exp->GetRight()));
    if (auto left_bool_val = std::dynamic_pointer_cast<Boolean>(left)) {
      auto right_bool_val = std::dynamic_pointer_cast<Boolean>(right);
      CHECK(right_bool_val != nullptr, "expect Boolean");
      return EvalBoolInfixExpression(infix_exp->GetOperator(), left, right);
    } else if (auto left_int_val = std::dynamic_pointer_cast<Integer>(left)) {
      auto right_int_val = std::dynamic_pointer_cast<Integer>(right);
      CHECK(right_int_val != nullptr, "expect Integer");
      return EvalIntInfixExpression(infix_exp->GetOperator(), left, right);
    } else {
      CHECK(false, "expect Boolean or Integer");
    }
  }
  return nullptr;
}
