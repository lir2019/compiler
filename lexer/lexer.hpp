#ifndef LEXER_LEXER_HPP
#define LEXER_LEXER_HPP

#include <string>
#include <vector>

#include "token.hpp"

class Lexer {
 public:
  Lexer(std::string str) : input_(str) { this->ReadChar(); };
  Token NextToken();

 private:
  void ReadChar();
  char PeekChar();
  void SkipWhiteSpace();
  std::string ReadIdentifier();
  std::string ReadNumber();
  std::string ReadString();

  std::string input_;
  int read_pos_ = 0;
  char ch_;
};

std::vector<Token> StrToTokens(std::string);

#endif  // LEXER_LEXER_HPP
