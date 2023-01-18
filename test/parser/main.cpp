#include "test/utils.hpp"
#include "ast/program.hpp"
#include "parser/parser.hpp"

static void Printer(std::string s) {
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
  Identifier x_ident(x_tok);
  Identifier y_ident(y_tok);
  auto x_let = std::make_shared<LetStmt>(let_tok, x_ident);
  auto y_let = std::make_shared<LetStmt>(let_tok, y_ident);
  expected.AppendStmt(x_let);
  expected.AppendStmt(y_let);
  Lexer lexer(input);
  Parser parser(lexer);
  Program res = parser.ParseProgram();
  auto expected_stmts = expected.GetStmts();
  auto res_stmts = res.GetStmts();
  Test("size equal", res_stmts.size(), expected_stmts.size());
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
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::IDENT failed: "
                               "expect next TokenType to be IDENT, but got Token(ASSIGN: \"=\")");
  try {
    Program res = parser.ParseProgram();
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
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::ASSIGN failed: "
                               "expect next TokenType to be ASSIGN, but got Token(SEMICOLON: \";\")");
  try {
    Program res = parser.ParseProgram();
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
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log("check next_tok_.type == TokenType::SEMICOLON failed: "
                               "expect next TokenType to be SEMICOLON, but got Token(COMMA: \",\")");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match", err_log, expected_err_log);
}

static void TestBase(const std::string &name, const std::string &input, const std::string &expected) {
  Lexer lexer(input);
  Parser parser(lexer);
  Program program = parser.ParseProgram();
  std::string res = program.ToString();
  Test(name, res, expected, Printer);
}

static void Test5() {
  std::string input = R"(
    let tmp =;
    let a =;
    return ;
  )";
  std::string expected = R"(Program{
let tmp = ();
let a = ();
return ();
}
)";
  TestBase("parse let and return statements", input, expected);
}

static void Test6() {
  std::string input = R"(
    return )
  )";
  Lexer lexer(input);
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

static void Test7() {
  std::string input = R"(
    foobar;
  )";
  std::string expected = R"(Program{
foobar;
}
)";
  TestBase("parse expression statement", input, expected);
}

static void Test8() {
  std::string input = R"(
    5;
  )";
  std::string expected = R"(Program{
5;
}
)";
  TestBase("parse expression statement", input, expected);
}

static void Test9() {
  std::string input = R"(
    !5;
    -a;
    --tmp;
    !!!10;
  )";
  std::string expected = R"(Program{
(!5);
(-a);
(-(-tmp));
(!(!(!10)));
}
)";
  TestBase("parse expression statement", input, expected);
}

static void Test10() {
  std::string input = R"(
    5+ 5;
    a / 55;
    5 * a + 55;
  )";
  std::string expected = R"(Program{
(5 + 5);
(a / 55);
((5 * a) + 55);
}
)";
  TestBase("parse expression statement", input, expected);
}

int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();
  Test8();
  Test9();
//  Test10();
}
