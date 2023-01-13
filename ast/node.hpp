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

  virtual std::string TokenLiteral() = 0;
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
  virtual std::string TokenLiteral() override;
  virtual void ExpressionNode() override;
private:
  Token tok_;  // TokenType::INDENT
  std::string value_;
};

class LetStmt : public IStatement {
public:
  virtual std::string TokenLiteral() override;
  virtual void StatementNode() override;
private:
  Token tok_;  // TokenType::LET
  std::shared_ptr<Identifier> ident_;
  std::shared_ptr<IExpression> value_;
};

#endif  // PARSER_NODE_HPP
