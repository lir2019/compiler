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
  MINUS,
  BANG,
  ASTERISK,
  SLASH,
  EQ,
  NE,
  LT,
  GT,
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  // keywords
  FUNCTION,
  LET,
  TRUE,
  FALSE,
  IF,
  ELSE,
  RETURN
};

std::string ToString(TokenType t);

struct Token {
  TokenType type;
  std::string literal;
};

std::ostream &operator<<(std::ostream &os, Token tok);
bool operator==(const Token &t1, const Token &t2);

TokenType LookUpIdent(const std::string &id);

#endif  // LEXER_TOKEN_HPP
