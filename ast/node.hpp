#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

#include <string>
#include <memory>

#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../common/utils.hpp"

class INode {
public:
  ~INode() {}

  virtual std::string TokenLiteral() const = 0;
  virtual void Print(std::ostream &os) const = 0;
};

class IStatement : public INode {
public:
  virtual void StatementNode() = 0;
};

class IExpression : public INode {
public:
  virtual void ExpressionNode() = 0;
};

class Identifier : public IExpression {
public:
  Identifier(Token tok) : tok_(tok) {}

  virtual std::string TokenLiteral() const override;
  virtual void Print(std::ostream &os) const override;
  virtual void ExpressionNode() override;
private:
  Token tok_;  // TokenType::INDENT
};

class LetStmt : public IStatement {
public:
  LetStmt(Token tok, std::shared_ptr<Identifier> ident, std::shared_ptr<IExpression> v) :
      tok_(tok), ident_(ident), value_(v) {}

  std::string GetIdent();

  virtual std::string TokenLiteral() const override;
  virtual void Print(std::ostream &os) const override;
  virtual void StatementNode() override;
private:
  Token tok_;  // TokenType::LET
  std::shared_ptr<Identifier> ident_;
  std::shared_ptr<IExpression> value_;
};

std::ostream &operator<<(std::ostream &os, const Identifier &ident);

std::ostream &operator<<(std::ostream &os, const LetStmt &let_stmt);

#endif  // PARSER_NODE_HPP
