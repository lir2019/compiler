#include "parser.hpp"

#include "../ast/program.hpp"

void Parser::NextToken() {
  cur_tok_ = next_tok_;
  next_tok_ = lexer_->NextToken();
}

std::shared_ptr<IStatement> Parser::ParseStatement() {
  switch (cur_tok_.type) {
    case TokenType::LET: return ParseLetStatement();
    case TokenType::RETURN: return ParseReturnStatement();
    default: return ParseExpressionStatement();
  }
  return nullptr;
}

std::shared_ptr<IStatement> Parser::ParseLetStatement() {
  CHECK(cur_tok_.type == TokenType::LET, "unexpected Token for LetStmt");
  CHECK(next_tok_.type == TokenType::IDENT,
        "expect next TokenType to be IDENT, but got " + next_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  Identifier ident(cur_tok_);
  CHECK(next_tok_.type == TokenType::ASSIGN,
        "expect next TokenType to be ASSIGN, but got " + next_tok_.ToString());
  NextToken();
  // TODO(lirui): deal with expression
  CHECK(next_tok_.type == TokenType::SEMICOLON,
        "expect next TokenType to be SEMICOLON, but got " + next_tok_.ToString());
  NextToken();

  return std::make_shared<LetStmt>(tok, ident);
}

std::shared_ptr<IStatement> Parser::ParseReturnStatement() {
  CHECK(cur_tok_.type == TokenType::RETURN,
        "expect current TokenType to be RETURN, but got " + cur_tok_.ToString());
  auto tok = cur_tok_;
  // TODO(lirui): deal with expression
  CHECK(next_tok_.type == TokenType::SEMICOLON,
        "expect next TokenType to be SEMICOLON, but got " + next_tok_.ToString());
  NextToken();

  return std::make_shared<ReturnStmt>(tok, nullptr);
}

std::shared_ptr<IStatement> Parser::ParseExpressionStatement() {
  auto tok = cur_tok_;
  auto exp = ParseExpression();
  return std::make_shared<ExpressionStmt>(tok, exp);
}

std::shared_ptr<IExpression> Parser::ParseExpression() {
  CHECK(cur_tok_.type == TokenType::IDENT,
        "expect current TokenType to be IDENT, but got " + cur_tok_.ToString());
  CHECK(next_tok_.type == TokenType::SEMICOLON,
        "expect next TokenType to be SEMICOLON, but got " + next_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  return std::make_shared<Identifier>(tok);
}

Program Parser::ParseProgram() {
  Program program;
  while (cur_tok_.type != TokenType::END) {
    auto stmt = ParseStatement();
    CHECK(stmt != nullptr, "unrecognized statement");
    if (stmt) {
      program.AppendStmt(stmt);
    }
    NextToken();
  }
  return program;
}
