#ifndef PARSER_EXPRESSION_HPP
#define PARSER_EXPRESSION_HPP

#include <string>
#include <memory>

#include "node.hpp"
#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../common/utils.hpp"

class IExpression : public INode {
 public:
  virtual ~IExpression();
  virtual void ExpressionNode() const = 0;
};

class Identifier : public IExpression {
 public:
  Identifier(Token tok) : tok_(tok) {}
  virtual ~Identifier() {}

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
  virtual ~IntegerLiteral() {}

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
  virtual ~Boolean() {}

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
  virtual ~PrefixExpression() {}

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
  virtual ~InfixExpression() {}

  DECL_DUMP_FUNCS(InfixExpression)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;

 private:
  Token tok_;  // binary operator, like +, -, *, /, ==, etc.
  std::shared_ptr<IExpression> left_;
  std::shared_ptr<IExpression> right_;
};

#endif  // PARSER_EXPRESSION_HPP
