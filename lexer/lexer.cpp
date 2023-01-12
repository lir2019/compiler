#include "lexer/lexer.hpp"

#include <vector>
#include <algorithm>

#include "lexer/utils.hpp"

void Lexer::ReadChar() {
  if (this->read_pos >= this->input.size()) {
    ch = '\0';
  } else {
    ch = this->input[this->read_pos];
  }
  this->read_pos++;
}

char Lexer::PeekChar() {
  if (this->read_pos >= this->input.size()) {
    return '\0';
  }
  return this->input[this->read_pos];
}

Token Lexer::NextToken() {
  this->SkipWhiteSpace();
  Token tok{TokenType::ILLEGAL, ""};
  tok.literal.push_back(this->ch);
#define CASE_CHAR_TOKEN(C, T) case C : { tok.type = TokenType::T; } break;
  switch (this->ch) {
    case '\0': {
      tok.type = TokenType::END;
      tok.literal = "";
    } break;
    case '=' : {
      if (PeekChar() == '=') {
        ReadChar();
        tok.literal.push_back(this->ch);
        tok.type = TokenType::EQ;
      } else {
        tok.type = TokenType::ASSIGN;
      }
    } break;
    case '!' : {
      if (PeekChar() == '=') {
        ReadChar();
        tok.literal.push_back(this->ch);
        tok.type = TokenType::NE;
      } else {
        tok.type = TokenType::BANG;
      }
    } break;
    CASE_CHAR_TOKEN(';', SEMICOLON)
    CASE_CHAR_TOKEN('(', LPAREN)
    CASE_CHAR_TOKEN(')', RPAREN)
    CASE_CHAR_TOKEN(',', COMMA)
    CASE_CHAR_TOKEN('+', PLUS)
    CASE_CHAR_TOKEN('{', LBRACE)
    CASE_CHAR_TOKEN('}', RBRACE)
    CASE_CHAR_TOKEN('-', MINUS)
    CASE_CHAR_TOKEN('*', ASTERISK)
    CASE_CHAR_TOKEN('/', SLASH)
    CASE_CHAR_TOKEN('<', LT)
    CASE_CHAR_TOKEN('>', GT)
    default: {
      if (IsLetter(this->ch)) {
        tok.literal = this->ReadIdentifier();
        tok.type = LookUpIdent(tok.literal);
        return tok;
      // TODO(lirui): support float
      } else if (IsNumber(this->ch)) {
        tok.literal = this->ReadNumber();
        tok.type = TokenType::INT;
        return tok;
      }
    } break;
  }
#undef CASE_CHAR_TOKEN
  this->ReadChar();
  return tok;
}

void Lexer::SkipWhiteSpace() {
  while (std::find(white_space_chars.begin(), white_space_chars.end(), this->ch) !=
         white_space_chars.end()) {
    this->ReadChar();
  }
}

std::string Lexer::ReadIdentifier() {
  int begin = this->read_pos - 1;
  while (IsLetter(this->ch)) {
    ReadChar();
  }
  int end = this->read_pos - 1;
  return this->input.substr(begin, end - begin);
}

std::string Lexer::ReadNumber() {
  int begin = this->read_pos - 1;
  while (IsNumber(this->ch)) {
    ReadChar();
  }
  int end = this->read_pos - 1;
  return this->input.substr(begin, end - begin);
}

std::vector<Token> StrToTokens(std::string input) {
  Lexer l(input);
  std::vector<Token> token_vec;
  Token tok;
  do {
    tok = l.NextToken();
    token_vec.push_back(tok);
  } while (tok.type != TokenType::END);
  return token_vec;
}
