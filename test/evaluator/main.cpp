#include "common/utils.hpp"
#include "test/utils.hpp"
#include "parser/parser.hpp"
#include "evaluator/evaluator.hpp"

static void Printer(std::string s) {
  std::cout << s << std::endl;
}

static void TestBase(const std::string &name,
                     const std::string &input,
                     const std::string &expected) {
  Lexer lexer(input);
  Parser parser(lexer);
  Program program = parser.ParseProgram();
  auto obj = Eval(program);
  auto res = obj->Inspect();
  Test(name, res, expected, Printer);
}

static void Test1() {
  std::string input = R"(
  5;
  )";
  std::string expected = "5";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate integer literal Test1", res, expected, Printer);
}

static void Test2() {
  std::string input = R"(
  true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate integer literal Test2", res, expected, Printer);
}

static void Test3() {
  std::string input = R"(
  !true;
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate integer literal Test3", res, expected, Printer);
}

static void Test4() {
  std::string input = R"(
  !!!!!false;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate integer literal Test4", res, expected, Printer);
}

static void Test5() {
  std::string input = R"(
  --5;
  )";
  std::string expected = "5";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate integer literal Test5", res, expected, Printer);
}

int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
}
