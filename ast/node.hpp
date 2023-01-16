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
  virtual void PrintNode(std::ostream &os) const = 0;
};

class IStatement : public INode {
public:
  virtual void StatementNode() const = 0;
};

class IExpression : public INode {
public:
  virtual void ExpressionNode() const = 0;
};

class Identifier : public IExpression {
public:
  Identifier(Token tok) : tok_(tok) {}

  DECL_DUMP_FUNCS(Identifier)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void ExpressionNode() const override;
private:
  Token tok_;  // TokenType::INDENT
};

class LetStmt : public IStatement {
public:
  LetStmt(const Token &tok, const Identifier &ident) :
      tok_(tok), ident_(std::make_shared<Identifier>(ident)) {}

  DECL_DUMP_FUNCS(LetStmt)

  std::string GetIdent();

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void StatementNode() const override;
private:
  Token tok_;  // TokenType::LET
  std::shared_ptr<Identifier> ident_;
  std::shared_ptr<IExpression> value_ = nullptr;
};

class ReturnStmt : public IStatement {
public:
  ReturnStmt(Token tok, std::shared_ptr<IExpression> v) : tok_(tok), value_(v) {}

  DECL_DUMP_FUNCS(ReturnStmt)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void StatementNode() const override;
private:
  Token tok_;  // TokenType::RETURN
  std::shared_ptr<IExpression> value_;
};

class ExpressionStmt : public IStatement {
public:
  ExpressionStmt(Token tok, std::shared_ptr<IExpression> exp) : tok_(tok), expression_(exp) {}

  DECL_DUMP_FUNCS(ExpressionStmt)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void StatementNode() const override;
private:
  Token tok_; // first Token in expression
  std::shared_ptr<IExpression> expression_;
};

#endif  // PARSER_NODE_HPP
