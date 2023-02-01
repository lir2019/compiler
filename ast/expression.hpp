#ifndef PARSER_EXPRESSION_HPP
#define PARSER_EXPRESSION_HPP

#include <string>
#include <memory>

#include "node.hpp"
#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../common/utils.hpp"

class IStatement;

class IExpression : public ClonableNode<IExpression> {
 public:
  virtual ~IExpression() = 0;
};

class Identifier : public IExpression {
 public:
  Identifier(const Token &tok) : tok_(std::make_shared<Token>(tok)) {}
  virtual ~Identifier() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(Identifier)

  std::string GetName() const { return tok_->literal; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::INDENT
};

class IntegerLiteral : public IExpression {
 public:
  IntegerLiteral(const Token &tok) : tok_(std::make_shared<Token>(tok)), value_(std::stol(tok.literal)) {}
  virtual ~IntegerLiteral() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(IntegerLiteral)

  int64_t GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::INT
  int64_t value_;
};

class BooleanLiteral : public IExpression {
 public:
  BooleanLiteral(const Token &tok) : tok_(std::make_shared<Token>(tok)), value_(tok.type == TokenType::TRUE) {}
  virtual ~BooleanLiteral() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(BooleanLiteral)

  bool GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::TRUE or TokenType::FALSE
  bool value_;
};

class PrefixExpression : public IExpression {
 public:
  PrefixExpression(const Token &tok, std::shared_ptr<IExpression> right)
      : tok_(std::make_shared<Token>(tok)), right_(right) {}
  virtual ~PrefixExpression() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(PrefixExpression)

  Token GetOperator() const { return *tok_; }
  std::shared_ptr<IExpression> GetRight() const { return right_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::BANG or TokenType::MINUS
  std::shared_ptr<IExpression> right_;
};

class InfixExpression : public IExpression {
 public:
  InfixExpression(const Token &tok,
                  std::shared_ptr<IExpression> left,
                  std::shared_ptr<IExpression> right)
      : tok_(std::make_shared<Token>(tok)), left_(left), right_(right) {}
  virtual ~InfixExpression() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(InfixExpression)

  Token GetOperator() const { return *tok_; }
  std::shared_ptr<IExpression> GetLeft() const { return left_; }
  std::shared_ptr<IExpression> GetRight() const { return right_; }

 private:
  std::shared_ptr<Token> tok_;  // binary operator, like +, -, *, /, ==, etc.
  std::shared_ptr<IExpression> left_;
  std::shared_ptr<IExpression> right_;
};

class IfExpression : public IExpression {
 public:
  IfExpression(const Token &tok,
               std::shared_ptr<IExpression> cond,
               std::shared_ptr<IStatement> consequence,
               std::shared_ptr<IStatement> alternative)
      : tok_(std::make_shared<Token>(tok)),
        cond_(cond),
        consequence_(consequence),
        alternative_(alternative) {}
  virtual ~IfExpression() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(IfExpression)

  std::shared_ptr<IExpression> GetCond() const { return cond_; }
  std::shared_ptr<IStatement> GetConsequence() const { return consequence_; }
  std::shared_ptr<IStatement> GetAlternative() const { return alternative_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::If
  std::shared_ptr<IExpression> cond_;
  std::shared_ptr<IStatement> consequence_;
  std::shared_ptr<IStatement> alternative_;
};

class FuncLiteral : public IExpression {
 public:
  FuncLiteral(const Token &tok,
              std::vector<Identifier> params,
              std::shared_ptr<IStatement> body)
      : tok_(std::make_shared<Token>(tok)), parameters_(params), body_(body) {}
  virtual ~FuncLiteral() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(FuncLiteral)

  std::vector<Identifier> GetParams() const { return parameters_; }
  std::shared_ptr<IStatement> GetBody() const { return body_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::FUNCTION
  std::vector<Identifier> parameters_;
  std::shared_ptr<IStatement> body_;
};

class CallExpression : public IExpression {
 public:
  CallExpression(const Token &tok,
                 std::shared_ptr<IExpression> func,
                 std::vector<std::shared_ptr<IExpression>> arguments)
      : tok_(std::make_shared<Token>(tok)), func_(func), arguments_(arguments) {}
  virtual ~CallExpression() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IExpression> Clone() const override;

  DECL_DUMP_FUNCS(CallExpression)

  std::shared_ptr<IExpression> GetFunc() const { return func_; }
  std::vector<std::shared_ptr<IExpression>> GetArgs() const {
    return arguments_;
  }

 private:
  std::shared_ptr<Token> tok_;                          // TokenType::FUNCTION
  std::shared_ptr<IExpression> func_;  // Identifier or FuncLiteral
  std::vector<std::shared_ptr<IExpression>> arguments_;
};

#endif  // PARSER_EXPRESSION_HPP
