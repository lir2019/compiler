#include "common/utils.hpp"
#include "test/utils.hpp"
#include "ast/statement.hpp"
#include "ast/program.hpp"
#include "parser/parser.hpp"

static void Printer(std::string s) {
  std::cout << s << std::endl;
}

static void TestBase(const std::string &name,
                     const std::string &input,
                     const std::string &expected) {
  Lexer lexer(input);
  Parser parser(lexer);
  Program program = parser.ParseProgram();
  std::string res = program.ToString();
  Test(name, res, expected, Printer);
}

static void Test1() {
  std::string input    = R"(
    let x = 1 + 1;
    let y = 5;
    let z = x;
  )";
  std::string expected = R"(Program{
let x = (1 + 1);
let y = 5;
let z = x;
}
)";
  TestBase("parse let statements Test1", input, expected);
}

static void Test2() {
  std::string input = R"(
    let = 1;
    let x a;
    let temp = x;
  )";
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log(
      "check cur_tok_.type == TokenType::IDENT failed: "
      "expect cur TokenType to be IDENT, but got Token(ASSIGN: \"=\")");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match Test2", err_log, expected_err_log, Printer);
}

static void Test3() {
  std::string input = R"(
    let x 3;
    let = 2;
    let temp = x;
  )";
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log(
      "check cur_tok_.type == TokenType::ASSIGN failed: "
      "expect cur TokenType to be ASSIGN, but got Token(INT: \"3\")");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match Test3", err_log, expected_err_log, Printer);
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
  std::string expected_err_log(
      "check is_found failed: no prefix parse function for COMMA found");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match Test4", err_log, expected_err_log, Printer);
}

static void Test5() {
  std::string input    = R"(
    let tmp = z;
    let a = 3;
    return 11 / a;
  )";
  std::string expected = R"(Program{
let tmp = z;
let a = 3;
return (11 / a);
}
)";
  TestBase("parse let and return statements Test5", input, expected);
}

static void Test6() {
  std::string input = R"(
    return )
  )";
  Lexer lexer(input);
  Parser parser(lexer);
  std::string err_log;
  std::string expected_err_log(
      "check is_found failed: no prefix parse function for RPAREN found");
  try {
    Program res = parser.ParseProgram();
  } catch (std::runtime_error err) {
    err_log = err.what();
  }
  Test("error log match Test6", err_log, expected_err_log, Printer);
}

static void Test7() {
  std::string input    = R"(
    foobar;
  )";
  std::string expected = R"(Program{
foobar;
}
)";
  TestBase("parse expression statement Test7", input, expected);
}

static void Test8() {
  std::string input    = R"(
    5;
  )";
  std::string expected = R"(Program{
5;
}
)";
  TestBase("parse expression statement Test8", input, expected);
}

static void Test9() {
  std::string input    = R"(
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
  TestBase("parse expression statement Test9", input, expected);
}

static void Test10() {
  std::string input    = R"(
-a * b;
!-a;
a + b +c;
a+b -c;
a*b*c;
a * b / c;
a + b / c;
a + b * c + d/ e -f;
3 + 4;
-5 * 5;
5 > 4 == 3 < 4;
5 < 4 != 3 > 4;
3 + 4*5 == 3*1 + 4*5;
  )";
  std::string expected = R"(Program{
((-a) * b);
(!(-a));
((a + b) + c);
((a + b) - c);
((a * b) * c);
((a * b) / c);
(a + (b / c));
(((a + (b * c)) + (d / e)) - f);
(3 + 4);
((-5) * 5);
((5 > 4) == (3 < 4));
((5 < 4) != (3 > 4));
((3 + (4 * 5)) == ((3 * 1) + (4 * 5)));
}
)";
  TestBase("parse expression statement Test10", input, expected);
}

static void Test11() {
  std::string input    = R"(
!true;
false;
3 > 5 == false;
3 < 5 == true;
  )";
  std::string expected = R"(Program{
(!true);
false;
((3 > 5) == false);
((3 < 5) == true);
}
)";
  TestBase("parse expression statement Test11", input, expected);
}

static void Test12() {
  std::string input    = R"(
    1 + (2 + 3) + 4;
    (5+5) * 2;
    2/(5+ 5);
    -(5 + 5);
    !(true == true);
    (3-(2*(5-1)-2)) / 2;
  )";
  std::string expected = R"(Program{
((1 + (2 + 3)) + 4);
((5 + 5) * 2);
(2 / (5 + 5));
(-(5 + 5));
(!(true == true));
((3 - ((2 * (5 - 1)) - 2)) / 2);
}
)";
  TestBase("parse expression statement Test12", input, expected);
}

static void Test13() {
  std::string input    = R"(
  {
  x+ y;
  5 *(u +v);}
  )";
  std::string expected = R"(Program{
{
(x + y);
(5 * (u + v));
}
}
)";
  TestBase("parse expression statement Test13", input, expected);
}

static void Test14() {
  std::string input    = R"(
  if (x + 2) {
  x == y;
  5 != (u +v) / 2;};
  )";
  std::string expected = R"(Program{
if (x + 2) {
(x == y);
(5 != ((u + v) / 2));
};
}
)";
  TestBase("parse expression statement Test14", input, expected);
}

static void Test15() {
  std::string input    = R"(
  if (x> 1) {
  a + 3;
  } else {
  a - 3;
  };
  )";
  std::string expected = R"(Program{
if (x > 1) {
(a + 3);
} else {
(a - 3);
};
}
)";
  TestBase("parse expression statement Test15", input, expected);
}

static void Test16() {
  std::string input    = R"(
  fn(x, y) {x + y;};
  fn() {};
fn(xx) { };
let add = fn(a, b) {return a + b;};
  )";
  std::string expected = R"(Program{
fn(x, y) {
(x + y);
};
fn() {
};
fn(xx) {
};
let add = fn(a, b) {
return (a + b);
};
}
)";
  TestBase("parse expression statement Test16", input, expected);
}

static void Test17() {
  std::string input    = R"(
  add(1, 2 *3, 4+ a);
a + add(b * c) +d;
add(a, b, 1, 2 * 3, 5 + 4, add(6, 7 * 8));
add(a + b + c * d /f + g);
fn(x, y) {x+y;}(1, sub(tmp, 1));
  )";
  std::string expected = R"(Program{
add(1, (2 * 3), (4 + a));
((a + add((b * c))) + d);
add(a, b, 1, (2 * 3), (5 + 4), add(6, (7 * 8)));
add((((a + b) + ((c * d) / f)) + g));
fn(x, y) {
(x + y);
}(1, sub(tmp, 1));
}
)";
  TestBase("parse expression statement Test17", input, expected);
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
  Test10();
  Test11();
  Test12();
  Test13();
  Test14();
  Test15();
  Test16();
  Test17();
}
