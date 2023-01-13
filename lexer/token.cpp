#include "token.hpp"

#include <map>

std::string ToString(TokenType t) {
#define CASE_TOKENTYPE_TOSTRING(T) case TokenType::T : return #T;
  switch (t) {
    CASE_TOKENTYPE_TOSTRING(ILLEGAL)
    CASE_TOKENTYPE_TOSTRING(END)
    CASE_TOKENTYPE_TOSTRING(IDENT)
    CASE_TOKENTYPE_TOSTRING(INT)
    CASE_TOKENTYPE_TOSTRING(ASSIGN)
    CASE_TOKENTYPE_TOSTRING(PLUS)
    CASE_TOKENTYPE_TOSTRING(MINUS)
    CASE_TOKENTYPE_TOSTRING(BANG)
    CASE_TOKENTYPE_TOSTRING(ASTERISK)
    CASE_TOKENTYPE_TOSTRING(SLASH)
    CASE_TOKENTYPE_TOSTRING(LT)
    CASE_TOKENTYPE_TOSTRING(GT)
    CASE_TOKENTYPE_TOSTRING(NE)
    CASE_TOKENTYPE_TOSTRING(EQ)
    CASE_TOKENTYPE_TOSTRING(COMMA)
    CASE_TOKENTYPE_TOSTRING(SEMICOLON)
    CASE_TOKENTYPE_TOSTRING(LPAREN)
    CASE_TOKENTYPE_TOSTRING(RPAREN)
    CASE_TOKENTYPE_TOSTRING(LBRACE)
    CASE_TOKENTYPE_TOSTRING(RBRACE)
    CASE_TOKENTYPE_TOSTRING(FUNCTION)
    CASE_TOKENTYPE_TOSTRING(LET)
    CASE_TOKENTYPE_TOSTRING(TRUE)
    CASE_TOKENTYPE_TOSTRING(FALSE)
    CASE_TOKENTYPE_TOSTRING(IF)
    CASE_TOKENTYPE_TOSTRING(ELSE)
    CASE_TOKENTYPE_TOSTRING(RETURN)
  }
#undef CASE_TOKENTYPE_TOSTRING
  return "";
}

std::ostream &operator<<(std::ostream &os, Token tok) {
  os << ToString(tok.type) << ": " << tok.literal;
  return os;
}

bool operator==(const Token &t1, const Token &t2) {
  return t1.type == t2.type && t1.literal == t2.literal;
}

TokenType LookUpIdent(const std::string &id) {
  static const std::map<std::string, TokenType> keywords{
    {"fn", TokenType::FUNCTION},
    {"let", TokenType::LET},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"return", TokenType::RETURN},
  };
  auto found_iter = keywords.find(id);
  if (found_iter != keywords.end()) {
    return found_iter->second;
  }
  return TokenType::IDENT;
}
