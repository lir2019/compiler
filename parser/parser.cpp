#include "parser.hpp"

#include "../ast/program.hpp"

void Parser::NextToken() {
  cur_tok_ = next_tok_;
  next_tok_ = lex_->NextToken();
}

std::shared_ptr<IStatement> Parser::ParseStatement() {
  switch (cur_tok_.type) {
    case TokenType::LET: return ParseLetStatement();
  }
  return nullptr;
}

std::shared_ptr<IStatement> Parser::ParseLetStatement() {
  CHECK(cur_tok_.type == TokenType::LET, "unexpected Token for LetStmt");
  CHECK(next_tok_.type == TokenType::IDENT,
        "expect next TokenType to be IDENT, but got " + next_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  auto ident = std::make_shared<Identifier>(cur_tok_);
  CHECK(next_tok_.type == TokenType::ASSIGN,
        "expect next TokenType to be ASSIGN, but got " + next_tok_.ToString());
  NextToken();
  // TODO(lirui): deal with expression
  CHECK(next_tok_.type == TokenType::SEMICOLON,
        "expect next TokenType to be SEMICOLON, but got " + next_tok_.ToString());

  return std::make_shared<LetStmt>(tok, ident, nullptr);
}

Program Parser::ParseProgram() {
  Program program;
  while (cur_tok_.type != TokenType::END) {
    auto stmt = ParseStatement();
    if (stmt) {
      program.AppendStmt(stmt);
    }
    NextToken();
  }
  return program;
}
