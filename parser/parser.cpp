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
  return nullptr;
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
