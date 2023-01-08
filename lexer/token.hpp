#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

#include <string>
#include <iostream>

enum class TokenType {
  ILLEGAL,
  END,
  IDENT,
  INT,
  ASSIGN,
  PLUS,
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  // keywords
  FUNCTION,
  LET
};

std::string ToString(TokenType t);

struct Token {
  TokenType type;
  std::string literal;
};

std::ostream &operator<<(std::ostream &os, Token tok);
bool operator==(const Token &t1, const Token &t2);

#endif  // LEXER_TOKEN_HPP
