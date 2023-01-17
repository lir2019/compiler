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
    cur_tok_ = lexer_->NextToken();
    next_tok_ = lexer_->NextToken();
    PARSE_EXP_FUNC_TYPE pre_parse_ident = std::bind(&Parser::ParseIdentifier, this);
    prefix_parse_funcs_.insert(std::make_pair(TokenType::IDENT, pre_parse_ident));
  }
  Program ParseProgram();
private:
  void NextToken();
  std::shared_ptr<IStatement> ParseStatement();
  std::shared_ptr<IStatement> ParseLetStatement();
  std::shared_ptr<IStatement> ParseReturnStatement();
  std::shared_ptr<IStatement> ParseExpressionStatement();
  std::shared_ptr<IExpression> ParseExpression();
  std::shared_ptr<IExpression> ParseIdentifier();

  std::shared_ptr<Lexer> lexer_;
  Token cur_tok_;
  Token next_tok_;
  std::map<TokenType, PARSE_EXP_FUNC_TYPE> prefix_parse_funcs_;
  std::map<TokenType, PARSE_EXP_FUNC_TYPE> infix_parse_funcs_;
};

#endif  // PARSER_PARSER_HPP
