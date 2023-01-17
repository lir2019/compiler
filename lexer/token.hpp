#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

#include <string>
#include <iostream>
#include <map>

#include "../common/utils.hpp"

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

enum class Precedence : unsigned short {
  LOWEST,
  EQUAL, // ==
  LESSGREATER, // >, <
  SUM, // +, -
  PRODUCT, // *, /
  PREFIX, // !
  CALL, // func(args)
};

inline Precedence GetPrecedence(TokenType t) {
  static std::map<TokenType, Precedence> token_precedence_map = {
    {TokenType::EQ, Precedence::EQUAL},
    {TokenType::NE, Precedence::EQUAL},
    {TokenType::LT, Precedence::LESSGREATER},
    {TokenType::GT, Precedence::LESSGREATER},
    {TokenType::PLUS, Precedence::SUM},
    {TokenType::MINUS, Precedence::SUM},
    {TokenType::SLASH, Precedence::PRODUCT},
    {TokenType::ASTERISK, Precedence::PRODUCT},
  };
  if (token_precedence_map.find(t) != token_precedence_map.end()) {
    return token_precedence_map[t];
  }
  return Precedence::LOWEST;
}

std::string ToString(TokenType t);

struct Token {
  DECL_DUMP_FUNCS(Token)

  TokenType type;
  std::string literal;
};

bool operator==(const Token &t1, const Token &t2);

TokenType LookUpIdent(const std::string &id);

#endif  // LEXER_TOKEN_HPP
