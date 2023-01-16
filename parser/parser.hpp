#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include <memory>

#include "../lexer/token.hpp"
#include "../lexer/lexer.hpp"
#include "../ast/program.hpp"

class Parser {
public:
  Parser(std::shared_ptr<Lexer> l) : lex_(l) {
    cur_tok_ = l->NextToken();
    next_tok_ = l->NextToken();
  }
  Program ParseProgram();
private:
  void NextToken();
  std::shared_ptr<IStatement> ParseStatement();
  std::shared_ptr<IStatement> ParseLetStatement();
  std::shared_ptr<IStatement> ParseReturnStatement();

  std::shared_ptr<Lexer> lex_;
  Token cur_tok_;
  Token next_tok_;
};

#endif  // PARSER_PARSER_HPP
