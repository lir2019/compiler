#include "lexer.hpp"

#include <vector>
#include <algorithm>

#include "utils.hpp"

void Lexer::ReadChar() {
  if (this->read_pos_ >= this->input_.size()) {
    ch_ = '\0';
  } else {
    ch_ = this->input_[this->read_pos_];
  }
  this->read_pos_++;
}

char Lexer::PeekChar() {
  if (this->read_pos_ >= this->input_.size()) {
    return '\0';
  }
  return this->input_[this->read_pos_];
}

Token Lexer::NextToken() {
  this->SkipWhiteSpace();
  Token tok{TokenType::ILLEGAL, ""};
  tok.literal.push_back(this->ch_);
#define CASE_CHAR_TOKEN(C, T) \
  case C: {                   \
    tok.type = TokenType::T;  \
  } break;
  switch (this->ch_) {
    case '\0': {
      tok.type = TokenType::END;
      tok.literal = "";
    } break;
    case '=': {
      if (PeekChar() == '=') {
        ReadChar();
        tok.literal.push_back(this->ch_);
        tok.type = TokenType::EQ;
      } else {
        tok.type = TokenType::ASSIGN;
      }
    } break;
    case '!': {
      if (PeekChar() == '=') {
        ReadChar();
        tok.literal.push_back(this->ch_);
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
    case '"': {
      tok.type = TokenType::STRING;
      tok.literal = this->ReadString();
    } break;
    default: {
      if (IsLetter(this->ch_)) {
        tok.literal = this->ReadIdentifier();
        tok.type = LookUpIdent(tok.literal);
      } else if (IsNumber(this->ch_)) {
        tok.literal = this->ReadNumber();
        tok.type = TokenType::INT;
        // TODO(lirui): support float
      }
    } break;
  }
#undef CASE_CHAR_TOKEN
  this->ReadChar();
  return tok;
}

void Lexer::SkipWhiteSpace() {
  while (std::find(white_space_chars.begin(), white_space_chars.end(),
                   this->ch_) != white_space_chars.end()) {
    this->ReadChar();
  }
}

std::string Lexer::ReadString() {
  CHECK(this->ch_ == '"', "expect current char to be \"");
  int begin = this->read_pos_;
  ReadChar();
  while (this->ch_ != '"' && this->ch_ != '\0') {
    ReadChar();
  }
  CHECK(this->ch_ == '"', "miss \" at the end of string literal");
  int end = this->read_pos_ - 1;
  return this->input_.substr(begin, end - begin);
}

std::string Lexer::ReadIdentifier() {
  CHECK(IsLetter(this->ch_), "expect current char to be letter");
  int begin = this->read_pos_ - 1;
  while (IsLetter(this->PeekChar())) {
    ReadChar();
  }
  int end = this->read_pos_;
  return this->input_.substr(begin, end - begin);
}

std::string Lexer::ReadNumber() {
  CHECK(IsNumber(this->ch_), "expect current char to be number");
  int begin = this->read_pos_ - 1;
  while (IsNumber(this->PeekChar())) {
    ReadChar();
  }
  int end = this->read_pos_;
  return this->input_.substr(begin, end - begin);
}

std::vector<Token> StrToTokens(std::string input_) {
  Lexer l(input_);
  std::vector<Token> token_vec;
  Token tok;
  do {
    tok = l.NextToken();
    token_vec.push_back(tok);
  } while (tok.type != TokenType::END);
  return token_vec;
}
