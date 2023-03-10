#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include <memory>
#include <map>
#include <functional>

#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../ast/program.hpp"

class Parser {
 public:
  using PARSE_EXP_FUNC_TYPE = std::function<std::shared_ptr<IExpression>()>;

  Parser(const Lexer &l) : lexer_(std::make_shared<Lexer>(l)) {
    cur_tok_  = lexer_->NextToken();
    next_tok_ = lexer_->NextToken();
    PARSE_EXP_FUNC_TYPE parse_func;
#define REGISTER_PRE_PARSE_FUNC(TOKEN_TYPE, PRE_PARSE_FUNC) \
  parse_func = std::bind(&Parser::PRE_PARSE_FUNC, this);    \
  prefix_parse_funcs_.insert(std::make_pair(TokenType::TOKEN_TYPE, parse_func));

    REGISTER_PRE_PARSE_FUNC(IDENT, ParseIdentifier)
    REGISTER_PRE_PARSE_FUNC(INT, ParseIntegerLiteral)
    REGISTER_PRE_PARSE_FUNC(TRUE, ParseBooleanLiteral)
    REGISTER_PRE_PARSE_FUNC(FALSE, ParseBooleanLiteral)
    REGISTER_PRE_PARSE_FUNC(STRING, ParseStringLiteral)
    REGISTER_PRE_PARSE_FUNC(LPAREN, ParseGroupedExpression)
    REGISTER_PRE_PARSE_FUNC(MINUS, ParsePrefixExpression)
    REGISTER_PRE_PARSE_FUNC(BANG, ParsePrefixExpression)
    REGISTER_PRE_PARSE_FUNC(IF, ParseIfExpression)
    REGISTER_PRE_PARSE_FUNC(FUNCTION, ParseFuncLiteral)
#undef REGISTER_PRE_PARSE_FUNC
  }
  Program ParseProgram();

  std::shared_ptr<IStatement> ParseStatement();
  std::shared_ptr<IStatement> ParseLetStatement();
  std::shared_ptr<IStatement> ParseReturnStatement();
  std::shared_ptr<IStatement> ParseExpressionStatement();
  std::shared_ptr<IStatement> ParseBlockStatement();

  std::shared_ptr<IExpression> ParseExpression(
      Precedence pre_preced = Precedence::LOWEST);
  std::shared_ptr<IExpression> ParseIdentifier();
  std::shared_ptr<IExpression> ParseIntegerLiteral();
  std::shared_ptr<IExpression> ParseFuncLiteral();
  std::shared_ptr<IExpression> ParseGroupedExpression();
  std::shared_ptr<IExpression> ParseBooleanLiteral();
  std::shared_ptr<IExpression> ParseStringLiteral();
  std::shared_ptr<IExpression> ParsePrefixExpression();
  std::shared_ptr<IExpression> ParseIfExpression();
  std::shared_ptr<IExpression> ParseCallExpression(
      std::shared_ptr<IExpression> func);

 private:
  void NextToken();

  std::shared_ptr<Lexer> lexer_;
  Token cur_tok_;
  Token next_tok_;
  std::map<TokenType, PARSE_EXP_FUNC_TYPE> prefix_parse_funcs_;
  std::map<TokenType, PARSE_EXP_FUNC_TYPE> infix_parse_funcs_;
};

#endif  // PARSER_PARSER_HPP
