
#include "test/utils.hpp"
#include "ast/program.hpp"
#include "ast/node.hpp"
#include "parser/parser.hpp"

static void Printer(size_t s) {
  std::cout << s << std::endl;
}

void Test1() {
  std::string input = R"(
    let x = ;
    let y = ;
  )";
  Program expected;
  Token let_tok{TokenType::LET, "let"};
  Token x_tok{TokenType::IDENT, "x"};
  Token y_tok{TokenType::IDENT, "y"};
  auto x_ident = std::make_shared<Identifier>(x_tok);
  auto y_ident = std::make_shared<Identifier>(y_tok);
  auto x_let = std::make_shared<LetStmt>(let_tok, x_ident, nullptr);
  auto y_let = std::make_shared<LetStmt>(let_tok, y_ident, nullptr);
  expected.AppendStmt(x_let);
  expected.AppendStmt(y_let);
  auto l = std::make_shared<Lexer>(input);
  Parser p(l);
  Program res = p.ParseProgram();
  auto expected_stmts = expected.GetStmts();
  auto res_stmts = res.GetStmts();
  res.Print(std::cout);
  expected.Print(std::cout);
  Test("size equal", res_stmts.size(), expected_stmts.size(), Printer);
  if (res_stmts.size() == expected_stmts.size()) {
    for (int64_t i = 0; i < res_stmts.size(); i++) {
      Test("is LetStmt", IsA<IStatement, LetStmt>(res_stmts[i]), true);
      Test("is LetStmt", IsA<IStatement, LetStmt>(expected_stmts[i]), true);
      auto res_let = std::dynamic_pointer_cast<LetStmt>(res_stmts[i]);
      auto expected_let = std::dynamic_pointer_cast<LetStmt>(expected_stmts[i]);
      Test("dynamic cast", res_let != nullptr, true);
      Test("dynamic cast", expected_let != nullptr, true);
      Test("identifiers are the same", res_let->GetIdent(), expected_let->GetIdent());
    }
  }
}

int main() {
  Test1();
}
