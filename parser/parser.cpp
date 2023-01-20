#include "parser.hpp"

#include <map>

#include "../ast/program.hpp"
#include "../ast/statement.hpp"

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

// IStatement::~IStatement() {}
// LetStmt::~LetStmt() {}
// ReturnStmt::~ReturnStmt() {}
// ExpressionStmt::~ExpressionStmt() {}

void Parser::NextToken() {
  cur_tok_ = next_tok_;
  next_tok_ = lexer_->NextToken();
}

std::shared_ptr<IStatement> Parser::ParseStatement() {
  switch (cur_tok_.type) {
    case TokenType::LET:
      return ParseLetStatement();
    case TokenType::RETURN:
      return ParseReturnStatement();
    default:
      return ParseExpressionStatement();
  }
  return nullptr;
}

std::shared_ptr<IStatement> Parser::ParseLetStatement() {
  CHECK(cur_tok_.type == TokenType::LET, "unexpected Token for LetStmt");
  auto tok = cur_tok_;
  NextToken();
  CHECK(cur_tok_.type == TokenType::IDENT,
        "expect cur TokenType to be IDENT, but got " + cur_tok_.ToString());
  Identifier ident(cur_tok_);
  NextToken();
  CHECK(cur_tok_.type == TokenType::ASSIGN,
        "expect cur TokenType to be ASSIGN, but got " + cur_tok_.ToString());
  NextToken();
  auto exp = ParseExpression();
  CHECK(cur_tok_.type == TokenType::SEMICOLON,
        "expect current TokenType to be SEMICOLON, but got " +
            cur_tok_.ToString());

  return std::make_shared<LetStmt>(tok, ident, exp);
}

std::shared_ptr<IStatement> Parser::ParseReturnStatement() {
  CHECK(
      cur_tok_.type == TokenType::RETURN,
      "expect current TokenType to be RETURN, but got " + cur_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  auto exp = ParseExpression();
  CHECK(cur_tok_.type == TokenType::SEMICOLON,
        "expect cur TokenType to be SEMICOLON, but got " + cur_tok_.ToString());

  return std::make_shared<ReturnStmt>(tok, exp);
}

std::shared_ptr<IStatement> Parser::ParseExpressionStatement() {
  auto tok = cur_tok_;
  auto exp = ParseExpression();
  return std::make_shared<ExpressionStmt>(tok, exp);
}

std::shared_ptr<IExpression> Parser::ParseExpression(Precedence pre_preced) {
  bool is_legal =
      prefix_parse_funcs_.find(cur_tok_.type) != prefix_parse_funcs_.end();
  CHECK(is_legal, "unexpected Token for Expression");
  auto prefix_parse_func = prefix_parse_funcs_[cur_tok_.type];
  auto left_exp = prefix_parse_func();
  while (cur_tok_.type != TokenType::SEMICOLON &&
         cur_tok_.type != TokenType::RPAREN &&
         pre_preced < GetPrecedence(cur_tok_.type)) {
    auto infix_tok = cur_tok_;
    auto cur_preced = GetPrecedence(cur_tok_.type);
    NextToken();
    auto right_exp = ParseExpression(cur_preced);
    left_exp =
        std::make_shared<InfixExpression>(infix_tok, left_exp, right_exp);
  }
  return left_exp;
}

std::shared_ptr<IExpression> Parser::ParseIdentifier() {
  CHECK(cur_tok_.type == TokenType::IDENT,
        "expect current TokenType to be IDENT, but got " + cur_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  return std::make_shared<Identifier>(tok);
}

std::shared_ptr<IExpression> Parser::ParseIntegerLiteral() {
  CHECK(cur_tok_.type == TokenType::INT,
        "expect current TokenType to be INT, but got " + cur_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  return std::make_shared<IntegerLiteral>(tok);
}

std::shared_ptr<IExpression> Parser::ParseGroupedExpression() {
  CHECK(
      cur_tok_.type == TokenType::LPAREN,
      "expect current TokenType to be LPAREN, but got " + cur_tok_.ToString());
  NextToken();
  auto exp = ParseExpression();
  CHECK(
      cur_tok_.type == TokenType::RPAREN,
      "expect current TokenType to be RPAREN, but got " + cur_tok_.ToString());
  NextToken();
  return exp;
}

std::shared_ptr<IExpression> Parser::ParseBoolean() {
  CHECK(cur_tok_.type == TokenType::TRUE || cur_tok_.type == TokenType::FALSE,
        "expect current TokenType to be TRUE or FALSE, but got " +
            cur_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  return std::make_shared<Boolean>(tok);
}

std::shared_ptr<IExpression> Parser::ParsePrefixExpression() {
  CHECK(cur_tok_.type == TokenType::BANG || cur_tok_.type == TokenType::MINUS,
        "expect current TokenType to be BANG or MINUS, but got " +
            cur_tok_.ToString());
  auto tok = cur_tok_;
  NextToken();
  auto right = ParseExpression(Precedence::PREFIX);
  return std::make_shared<PrefixExpression>(tok, right);
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
