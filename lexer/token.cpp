#include "lexer/token.hpp"

std::string ToString(TokenType t) {
#define CASE_TOKENTYPE_TOSTRING(T) case TokenType::T : return #T;
  switch (t) {
    CASE_TOKENTYPE_TOSTRING(ILLEGAL)
    CASE_TOKENTYPE_TOSTRING(END)
    CASE_TOKENTYPE_TOSTRING(IDENT)
    CASE_TOKENTYPE_TOSTRING(INT)
    CASE_TOKENTYPE_TOSTRING(ASSIGN)
    CASE_TOKENTYPE_TOSTRING(PLUS)
    CASE_TOKENTYPE_TOSTRING(COMMA)
    CASE_TOKENTYPE_TOSTRING(SEMICOLON)
    CASE_TOKENTYPE_TOSTRING(LPAREN)
    CASE_TOKENTYPE_TOSTRING(RPAREN)
    CASE_TOKENTYPE_TOSTRING(LBRACE)
    CASE_TOKENTYPE_TOSTRING(RBRACE)
    CASE_TOKENTYPE_TOSTRING(FUNCTION)
    CASE_TOKENTYPE_TOSTRING(LET)
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
