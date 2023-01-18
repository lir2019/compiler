#ifndef PARSER_STATEMENT_HPP
#define PARSER_STATEMENT_HPP

#include "node.hpp"
#include "expression.hpp"

class IStatement : public INode {
 public:
  virtual ~IStatement() = 0;
  virtual void StatementNode() const = 0;
};

class LetStmt : public IStatement {
 public:
  LetStmt(const Token &tok, const Identifier &ident)
      : tok_(tok), ident_(std::make_shared<Identifier>(ident)) {}
  virtual ~LetStmt();

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
  ReturnStmt(Token tok, std::shared_ptr<IExpression> v)
      : tok_(tok), value_(v) {}
  virtual ~ReturnStmt();

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
  ExpressionStmt(Token tok, std::shared_ptr<IExpression> exp)
      : tok_(tok), expression_(exp) {}
  virtual ~ExpressionStmt();

  DECL_DUMP_FUNCS(ExpressionStmt)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;
  virtual void StatementNode() const override;

 private:
  Token tok_;  // first Token in expression
  std::shared_ptr<IExpression> expression_;
};

#endif  // PARSER_STATEMENT_HPP