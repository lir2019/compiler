#ifndef PARSER_EXPRESSION_HPP
#define PARSER_EXPRESSION_HPP

#include <string>
#include <memory>

#include "node.hpp"
#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../common/utils.hpp"

class IStatement;

class IExpression : public INode {
 public:
  virtual ~IExpression()              = 0;
  virtual void ExpressionNode() const = 0;
};

class Identifier : public IExpression {
 public:
  Identifier(Token tok) : tok_(tok) {}
  virtual ~Identifier();

  DECL_DUMP_FUNCS(Identifier)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // TokenType::INDENT
};

class IntegerLiteral : public IExpression {
 public:
  IntegerLiteral(Token tok) : tok_(tok), value_(std::stol(tok.literal)) {}
  virtual ~IntegerLiteral();

  DECL_DUMP_FUNCS(IntegerLiteral)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // TokenType::INT
  int64_t value_;
};

class Boolean : public IExpression {
 public:
  Boolean(Token tok) : tok_(tok), value_(tok.type == TokenType::TRUE) {}
  virtual ~Boolean();

  DECL_DUMP_FUNCS(Boolean)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // TokenType::TRUE or TokenType::FALSE
  bool value_;
};

class PrefixExpression : public IExpression {
 public:
  PrefixExpression(Token tok, std::shared_ptr<IExpression> right)
      : tok_(tok), right_(right) {}
  virtual ~PrefixExpression();

  DECL_DUMP_FUNCS(PrefixExpression)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // TokenType::BANG or TokenType::MINUS
  std::shared_ptr<IExpression> right_;
};

class InfixExpression : public IExpression {
 public:
  InfixExpression(Token tok,
                  std::shared_ptr<IExpression> left,
                  std::shared_ptr<IExpression> right)
      : tok_(tok), left_(left), right_(right) {}
  virtual ~InfixExpression();

  DECL_DUMP_FUNCS(InfixExpression)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // binary operator, like +, -, *, /, ==, etc.
  std::shared_ptr<IExpression> left_;
  std::shared_ptr<IExpression> right_;
};

class IfExpression : public IExpression {
 public:
  IfExpression(Token tok,
               std::shared_ptr<IExpression> cond,
               std::shared_ptr<IStatement> consequence,
               std::shared_ptr<IStatement> alternative)
      : tok_(tok), cond_(cond), consequence_(consequence),
        alternative_(alternative) {}
  virtual ~IfExpression() {}

  DECL_DUMP_FUNCS(IfExpression)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_; // TokenType::If
  std::shared_ptr<IExpression> cond_;
  std::shared_ptr<IStatement> consequence_;
  std::shared_ptr<IStatement> alternative_;
};

class FuncLiteral : public IExpression {
 public:
  FuncLiteral(Token tok,
              std::vector<Identifier> params,
              std::shared_ptr<IStatement> body)
      : tok_(tok), parameters_(params), body_(body) {}
  virtual ~FuncLiteral() {}

  DECL_DUMP_FUNCS(FuncLiteral)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_; // TokenType::FUNCTION
  std::vector<Identifier> parameters_;
  std::shared_ptr<IStatement> body_;
};

class CallExpression : public IExpression {
 public:
  CallExpression(Token tok,
                 std::shared_ptr<IExpression> func,
                 std::vector<std::shared_ptr<IExpression>> arguments)
      : tok_(tok), func_(func), arguments_(arguments) {}
  virtual ~CallExpression() {}

  DECL_DUMP_FUNCS(CallExpression)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_; // TokenType::FUNCTION
  std::shared_ptr<IExpression> func_; // Identifier or FuncLiteral
  std::vector<std::shared_ptr<IExpression>> arguments_;
};

#endif  // PARSER_EXPRESSION_HPP
