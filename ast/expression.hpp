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

#endif  // PARSER_EXPRESSION_HPP
