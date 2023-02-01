#ifndef PARSER_STATEMENT_HPP
#define PARSER_STATEMENT_HPP

#include <vector>

#include "node.hpp"
#include "expression.hpp"

class LetStmt : public IStatement {
 public:
  LetStmt(const Token &tok,
          const Identifier &ident,
          const IExpression &value)
      : tok_(std::make_shared<Token>(tok)),
        ident_(std::make_shared<Identifier>(ident)),
        value_(value.Clone()) {}
  virtual ~LetStmt();

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IStatement> Clone() const override;

  DECL_DUMP_FUNCS(LetStmt)

  std::shared_ptr<Identifier> GetIdent() const { return ident_; }
  std::shared_ptr<IExpression> GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::LET
  std::shared_ptr<Identifier> ident_;
  std::shared_ptr<IExpression> value_;
};

class ReturnStmt : public IStatement {
 public:
  ReturnStmt(const Token &tok, const IExpression &value)
      : tok_(std::make_shared<Token>(tok)),
        value_(value.Clone()) {}
  virtual ~ReturnStmt() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IStatement> Clone() const override;

  DECL_DUMP_FUNCS(ReturnStmt)

  std::shared_ptr<IExpression> GetValue() const { return value_; }

 private:
  std::shared_ptr<Token> tok_;  // TokenType::RETURN
  std::shared_ptr<IExpression> value_;
};

class ExpressionStmt : public IStatement {
 public:
  ExpressionStmt(const Token &tok, const IExpression &exp)
      : tok_(std::make_shared<Token>(tok)),
        expression_(exp.Clone()) {}
  virtual ~ExpressionStmt() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IStatement> Clone() const override;

  DECL_DUMP_FUNCS(ExpressionStmt)

  std::shared_ptr<IExpression> GetExp() const { return expression_; }

 private:
  std::shared_ptr<Token> tok_;  // first Token in expression
  std::shared_ptr<IExpression> expression_;
};

class BlockStmt : public IStatement {
 public:
  BlockStmt(const Token &tok) : tok_(std::make_shared<Token>(tok)) {}
  virtual ~BlockStmt() {}

  virtual void PrintNode(std::ostream &os) const override;
  virtual std::shared_ptr<IStatement> Clone() const override;

  DECL_DUMP_FUNCS(BlockStmt)

  void AppendStmt(std::shared_ptr<IStatement> stmt) { stmts_.push_back(stmt); }
  std::vector<std::shared_ptr<IStatement>> GetStmts() const { return stmts_; }

 private:
  std::shared_ptr<Token> tok_;  // {
  std::vector<std::shared_ptr<IStatement>> stmts_;
};

#endif  // PARSER_STATEMENT_HPP
