#ifndef LEXER_LEXER_HPP
#define LEXER_LEXER_HPP

#include <string>
#include <vector>

#include "lexer/token.hpp"

class Lexer {
public:
  Lexer(std::string str) : input(str) { this->ReadChar(); };
  Token NextToken();
private:
  void ReadChar();
  void SkipWhiteSpace();
  std::string ReadIdentifier();
  std::string ReadNumber();

  std::string input;
  int read_pos = 0;
  char ch;
};

TokenType LookUpIdent(const std::string &id);

std::vector<Token> StrToTokens(std::string);

#endif  // LEXER_LEXER_HPP
