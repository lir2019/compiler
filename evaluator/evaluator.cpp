#include "evaluator.hpp"

#include "../ast/program.hpp"

namespace {

std::shared_ptr<IObject> EvalPrefixExpression(
    Token op,
    std::shared_ptr<IObject> right,
    std::shared_ptr<Environment> env) {
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
    default:
      return nullptr;
  }
}

#define CASE_INFIX_EVAL(TYPE, NAME, OP)                          \
  case TokenType::NAME: {                                        \
    return std::make_shared<TYPE>(left_val->GetValue()           \
                                      OP right_val->GetValue()); \
  } break;

std::shared_ptr<IObject> EvalBoolInfixExpression(
    Token op,
    std::shared_ptr<IObject> left,
    std::shared_ptr<IObject> right,
    std::shared_ptr<Environment> env) {
  auto left_val  = std::dynamic_pointer_cast<Boolean>(left);
  auto right_val = std::dynamic_pointer_cast<Boolean>(right);
  CHECK(left_val != nullptr && right_val != nullptr,
        "expect both to be Boolean");
  switch (op.type) {
    CASE_INFIX_EVAL(Boolean, EQ, ==)
    CASE_INFIX_EVAL(Boolean, NE, !=)
    default:
      CHECK(false, "expect TokenType to be EQ or NE, but got " + op.ToString());
  }
  return nullptr;
}

std::shared_ptr<IObject> EvalIntInfixExpression(
    Token op,
    std::shared_ptr<IObject> left,
    std::shared_ptr<IObject> right,
    std::shared_ptr<Environment> env) {
  auto left_val  = std::dynamic_pointer_cast<Integer>(left);
  auto right_val = std::dynamic_pointer_cast<Integer>(right);
  CHECK(left_val != nullptr && right_val != nullptr,
        "expect both to be Integer");
  switch (op.type) {
    CASE_INFIX_EVAL(Boolean, EQ, ==)
    CASE_INFIX_EVAL(Boolean, NE, !=)
    CASE_INFIX_EVAL(Boolean, GT, >)
    CASE_INFIX_EVAL(Boolean, LT, <)
    CASE_INFIX_EVAL(Integer, PLUS, +)
    CASE_INFIX_EVAL(Integer, MINUS, -)
    CASE_INFIX_EVAL(Integer, ASTERISK, *)
    CASE_INFIX_EVAL(Integer, SLASH, /)
    default:
      CHECK(false, "expect TokenType to be EQ or NE, but got " + op.ToString());
  }
  return nullptr;
}

#undef CASE_INT_INFIX_EVAL

std::shared_ptr<IObject> Eval(std::vector<std::shared_ptr<IStatement>> stmts,
                              std::shared_ptr<Environment> env) {
  std::shared_ptr<IObject> res;
  for (auto stmt : stmts) {
    res = Eval(*stmt, env);
    if (std::dynamic_pointer_cast<ReturnValue>(res)) {
      return res;
    }
  }
  return res;
}

std::shared_ptr<IObject> EvalIfExpression(const INode &node,
                                          std::shared_ptr<Environment> env) {
  auto if_exp = dynamic_cast<const IfExpression *>(&node);
  CHECK(if_exp != nullptr, "expect IfExpression");
  auto cond      = Eval(*(if_exp->GetCond()), env);
  auto cond_bool = std::dynamic_pointer_cast<Boolean>(cond);
  CHECK(cond_bool != nullptr, "expect Boolean");
  if (cond_bool->GetValue()) {
    if (auto consequence = if_exp->GetConsequence()) {
      return Eval(*consequence, env);
    }
  } else {
    if (auto alternative = if_exp->GetAlternative()) {
      return Eval(*alternative, env);
    }
  }
  return std::make_shared<Null>();
}

std::shared_ptr<IObject> ApplyFunction(
    std::shared_ptr<IObject> obj,
    std::vector<std::shared_ptr<IObject>> args) {
  auto func = std::dynamic_pointer_cast<Function>(obj);
  CHECK(func != nullptr, "expect Function");
  auto outer_env = func->GetEnv();
  auto env       = std::make_shared<Environment>(outer_env);
  auto params    = func->GetParams();
  CHECK(args.size() == params.size(),
        "arguments size does not match parameters size");
  for (int i = 0; i < args.size(); i++) {
    env->Set(params[i].GetName(), args[i]);
  }
  auto ret = Eval(*(func->GetBody()), env);
  if (auto ret_val = std::dynamic_pointer_cast<ReturnValue>(ret)) {
    return ret_val->GetValue();
  }
  return ret;
}

}  // namespace

#define IF_MATCH_THEN(TYPE, BODY)                   \
  if (auto ptr = dynamic_cast<const TYPE *>(&node)) \
  BODY

std::shared_ptr<IObject> Eval(const INode &node,
                              std::shared_ptr<Environment> env) {
  IF_MATCH_THEN(Program, { return Eval(ptr->GetStmts(), env); })
  else IF_MATCH_THEN(BlockStmt, {
    return Eval(ptr->GetStmts(), env);
  }) else IF_MATCH_THEN(ExpressionStmt, {
    return Eval(*(ptr->GetExp()), env);
  }) else IF_MATCH_THEN(LetStmt, {
    auto value = Eval(*(ptr->GetValue()), env);
    env->Set(ptr->GetIdent()->GetName(), value);
    return value;
  }) else if (auto ret_stmt = dynamic_cast<const ReturnStmt *>(&node)) {
    auto value = Eval(*(ret_stmt->GetValue()), env);
    return std::make_shared<ReturnValue>(value);
  }
  else if (auto ident = dynamic_cast<const Identifier *>(&node)) {
    return env->Get(ident->GetName());
  }
  else if (auto int_lit = dynamic_cast<const IntegerLiteral *>(&node)) {
    return std::make_shared<Integer>(int_lit->GetValue());
  }
  else if (auto bool_lit = dynamic_cast<const BooleanLiteral *>(&node)) {
    return std::make_shared<Boolean>(bool_lit->GetValue());
  }
  else if (auto prefix_exp = dynamic_cast<const PrefixExpression *>(&node)) {
    auto right = Eval(*(prefix_exp->GetRight()), env);
    return EvalPrefixExpression(prefix_exp->GetOperator(), right, env);
  }
  else if (auto infix_exp = dynamic_cast<const InfixExpression *>(&node)) {
    auto left  = Eval(*(infix_exp->GetLeft()), env);
    auto right = Eval(*(infix_exp->GetRight()), env);
    if (auto left_bool_val = std::dynamic_pointer_cast<Boolean>(left)) {
      auto right_bool_val = std::dynamic_pointer_cast<Boolean>(right);
      CHECK(right_bool_val != nullptr, "expect Boolean");
      return EvalBoolInfixExpression(infix_exp->GetOperator(), left, right,
                                     env);
    } else if (auto left_int_val = std::dynamic_pointer_cast<Integer>(left)) {
      auto right_int_val = std::dynamic_pointer_cast<Integer>(right);
      CHECK(right_int_val != nullptr, "expect Integer");
      return EvalIntInfixExpression(infix_exp->GetOperator(), left, right, env);
    } else {
      CHECK(false, "expect Boolean or Integer");
    }
  }
  else if (auto if_exp = dynamic_cast<const IfExpression *>(&node)) {
    return EvalIfExpression(node, env);
  }
  else if (auto func_lit = dynamic_cast<const FuncLiteral *>(&node)) {
    auto params = func_lit->GetParams();
    auto body   = func_lit->GetBody();
    return std::make_shared<Function>(params, body, env);
  }
  else if (auto call = dynamic_cast<const CallExpression *>(&node)) {
    auto func = Eval(*(call->GetFunc()), env);
    std::vector<std::shared_ptr<IObject>> args;
    for (auto arg_exp : call->GetArgs()) {
      args.push_back(Eval(*arg_exp, env));
    }
    return ApplyFunction(func, args);
  }
  else {
    CHECK(false, "unexpected Node to be evaluated");
  }
  return nullptr;
}

#undef IF_MATCH_THEN
