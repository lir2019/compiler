#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include <memory>

#include "lexer/lexer.hpp"

class Parser {
public:
  Parser(std::shared_ptr<Lexer> l) : lex_(l) {}
  void NextToken();
private:
  std::shared_ptr<Lexer> lex_;
  Token cur_tok_;
  Token next_tok_;
};

#endif  // PARSER_PARSER_HPP
