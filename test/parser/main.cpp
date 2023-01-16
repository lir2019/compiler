
#include "test/utils.hpp"
#include "ast/program.hpp"
#include "ast/node.hpp"
#include "parser/parser.hpp"

static void Printer(size_t s) {
  std::cout << s << std::endl;
}

static void Printer(const std::string &s) {
  std::cout << s << std::endl;
}

static void Test1() {
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

static void Test2() {
  std::string input = R"(
    let = ;
    let x ;
    let temp = ,
  )";
  auto l = std::make_shared<Lexer>(input);
  Parser p(l);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::IDENT failed: "
                               "expect next TokenType to be IDENT, but got Token(ASSIGN: \"=\")");
  try {
    Program res = p.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match", err_log, expected_err_log);
}

static void Test3() {
  std::string input = R"(
    let x ;
    let = ;
    let temp = ,
  )";
  auto l = std::make_shared<Lexer>(input);
  Parser p(l);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::ASSIGN failed: "
                               "expect next TokenType to be ASSIGN, but got Token(SEMICOLON: \";\")");
  try {
    Program res = p.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match", err_log, expected_err_log);
}

static void Test4() {
  std::string input = R"(
    let temp = ,
    let x ;
    let = ;
  )";
  auto l = std::make_shared<Lexer>(input);
  Parser p(l);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::SEMICOLON failed: "
                               "expect next TokenType to be SEMICOLON, but got Token(COMMA: \",\")");
  try {
    Program res = p.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match", err_log, expected_err_log);
}

static void TestBase(const std::string &name, const std::string &input, const std::string &expected) {
  auto lexer = std::make_shared<Lexer>(input);
  Parser parser(lexer);
  Program program = parser.ParseProgram();
  std::string res = program.ToString();
  std::cout << res << std::endl;
  std::cout << expected << std::endl;
  Test(name, res, expected);
}

static void Test5() {
  std::string input = R"(
    let tmp =;
    let a =;
    return ;
  )";
  std::string expected = R"(Program(
LetStmt(Token(LET: "let"), Identifier(Token(IDENT: "tmp")))
LetStmt(Token(LET: "let"), Identifier(Token(IDENT: "a")))
ReturnStmt(Token(RETURN: "return"))
)
)";
  TestBase("parse let and return", input, expected);
}

static void Test6() {
  std::string input = R"(
    return )
  )";
  auto lexer = std::make_shared<Lexer>(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::SEMICOLON failed: "
                               "expect next TokenType to be SEMICOLON, but got Token(RPAREN: \")\")");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match", err_log, expected_err_log);
}

int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
}
