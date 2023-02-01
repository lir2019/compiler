#ifndef PARSER_EXPRESSION_HPP
#define PARSER_EXPRESSION_HPP

#include <string>
#include <memory>

#include "node.hpp"
#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../common/utils.hpp"

class Identifier : public Expression<Identifier> {
 public:
  Identifier(const Token &tok) : tok_(std::make_shared<Token>(tok)) {}
  virtual ~Identifier() {}

  DECL_DUMP_FUNCS(Identifier)

  std::string GetName() const { return tok_->literal; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::INDENT
};

class IntegerLiteral : public Expression<IntegerLiteral> {
 public:
  IntegerLiteral(const Token &tok) : tok_(std::make_shared<Token>(tok)), value_(std::stol(tok.literal)) {}
  virtual ~IntegerLiteral() {}

  DECL_DUMP_FUNCS(IntegerLiteral)

  int64_t GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::INT
  int64_t value_;
};

class BooleanLiteral : public Expression<BooleanLiteral> {
 public:
  BooleanLiteral(const Token &tok) : tok_(std::make_shared<Token>(tok)), value_(tok.type == TokenType::TRUE) {}
  virtual ~BooleanLiteral() {}

  DECL_DUMP_FUNCS(BooleanLiteral)

  bool GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::TRUE or TokenType::FALSE
  bool value_;
};

class PrefixExpression : public Expression<PrefixExpression> {
 public:
  PrefixExpression(const Token &tok, const IExpression &right)
      : tok_(std::make_shared<Token>(tok)), right_(right.Clone()) {}
  virtual ~PrefixExpression() {}

  DECL_DUMP_FUNCS(PrefixExpression)

  Token GetOperator() const { return *tok_; }
  std::shared_ptr<IExpression> GetRight() const { return right_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::BANG or TokenType::MINUS
  std::shared_ptr<IExpression> right_;
};

class InfixExpression : public Expression<InfixExpression> {
 public:
  InfixExpression(const Token &tok,
                  const IExpression &left,
                  const IExpression &right)
      : tok_(std::make_shared<Token>(tok)), left_(left.Clone()), right_(right.Clone()) {}
  virtual ~InfixExpression() {}

  DECL_DUMP_FUNCS(InfixExpression)

  Token GetOperator() const { return *tok_; }
  std::shared_ptr<IExpression> GetLeft() const { return left_; }
  std::shared_ptr<IExpression> GetRight() const { return right_; }

 private:
  std::shared_ptr<Token> tok_;  // binary operator, like +, -, *, /, ==, etc.
  std::shared_ptr<IExpression> left_;
  std::shared_ptr<IExpression> right_;
};

class IfExpression : public Expression<IfExpression> {
 public:
  IfExpression(const Token &tok,
               const IExpression &cond,
               const IStatement &consequence)
      : tok_(std::make_shared<Token>(tok)),
        cond_(cond.Clone()),
        consequence_(consequence.Clone()),
        alternative_(nullptr) {}
  virtual ~IfExpression() {}

  DECL_DUMP_FUNCS(IfExpression)

  std::shared_ptr<IExpression> GetCond() const { return cond_; }
  std::shared_ptr<IStatement> GetConsequence() const { return consequence_; }
  std::shared_ptr<IStatement> GetAlternative() const { return alternative_; }
  void SetAlternative(const IStatement &alternative) {
    alternative_ = alternative.Clone();
  }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::If
  std::shared_ptr<IExpression> cond_;
  std::shared_ptr<IStatement> consequence_;
  std::shared_ptr<IStatement> alternative_;
};

class FuncLiteral : public Expression<FuncLiteral> {
 public:
  FuncLiteral(const Token &tok,
              const std::vector<Identifier> &params,
              const IStatement &body)
      : tok_(std::make_shared<Token>(tok)), parameters_(params), body_(body.Clone()) {}
  virtual ~FuncLiteral() {}

  DECL_DUMP_FUNCS(FuncLiteral)

  std::vector<Identifier> GetParams() const { return parameters_; }
  std::shared_ptr<IStatement> GetBody() const { return body_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::FUNCTION
  std::vector<Identifier> parameters_;
  std::shared_ptr<IStatement> body_;
};

class CallExpression : public Expression<CallExpression> {
 public:
  CallExpression(const Token &tok,
                 const IExpression &func)
      : tok_(std::make_shared<Token>(tok)), func_(func.Clone()), arguments_() {}
  virtual ~CallExpression() {}

  DECL_DUMP_FUNCS(CallExpression)

  std::shared_ptr<IExpression> GetFunc() const { return func_; }
  std::vector<std::shared_ptr<IExpression>> GetArgs() const {
    return arguments_;
  }
  void AppendArg(const IExpression &arg) {
    arguments_.push_back(arg.Clone());
  }

 private:
  std::shared_ptr<Token> tok_;                          // TokenType::FUNCTION
  std::shared_ptr<IExpression> func_;  // Identifier or FuncLiteral
  std::vector<std::shared_ptr<IExpression>> arguments_;
};

#endif  // PARSER_EXPRESSION_HPP
