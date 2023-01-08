#include "lexer/lexer.hpp"

#include <vector>
#include <map>
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

Token Lexer::NextToken() {
  this->SkipWhiteSpace();
  Token tok{TokenType::ILLEGAL, ""};
  tok.literal.push_back(this->ch);
  switch (this->ch) {
    case '\0': {
      tok.type = TokenType::END;
      tok.literal = "";
    } break;
    case '=' : {
      tok.type = TokenType::ASSIGN;
    } break;
    case ';' : {
      tok.type = TokenType::SEMICOLON;
    } break;
    case '(' : {
      tok.type = TokenType::LPAREN;
    } break;
    case ')' : {
      tok.type = TokenType::RPAREN;
    } break;
    case ',' : {
      tok.type = TokenType::COMMA;
    } break;
    case '+' : {
      tok.type = TokenType::PLUS;
    } break;
    case '{' : {
      tok.type = TokenType::LBRACE;
    } break;
    case '}' : {
      tok.type = TokenType::RBRACE;
    } break;
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

TokenType LookUpIdent(const std::string &id) {
  static const std::map<std::string, TokenType> keywords{
    {"fn", TokenType::FUNCTION},
    {"let", TokenType::LET},
  };
  auto found_iter = keywords.find(id);
  if (found_iter != keywords.end()) {
    return found_iter->second;
  }
  return TokenType::IDENT;
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
