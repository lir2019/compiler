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
  Test("evaluate Test1", res, expected, Printer);
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
  Test("evaluate Test2", res, expected, Printer);
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
  Test("evaluate Test3", res, expected, Printer);
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
  Test("evaluate Test4", res, expected, Printer);
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
  Test("evaluate Test5", res, expected, Printer);
}

static void Test6() {
  std::string input = R"(
  true == true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test6", res, expected, Printer);
}

static void Test7() {
  std::string input = R"(
  false != true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test7", res, expected, Printer);
}

static void Test8() {
  std::string input = R"(
  false == true;
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test8", res, expected, Printer);
}

static void Test9() {
  std::string input = R"(
  5 < 1 == false;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test9", res, expected, Printer);
}

static void Test10() {
  std::string input = R"(
  5 - 1 * 4 / 2;
  )";
  std::string expected = "3";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test10", res, expected, Printer);
}

static void Test11() {
  std::string input = R"(
  5 - 1 * 4 / 2 + 4 * 2 > 9;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test11", res, expected, Printer);
}

static void Test12() {
  std::string input = R"(
  ((4 - 1) * 2 / (2 + 4) * 2 == 2) == (2 == 3);
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto obj = Eval(*node);
  auto res = obj->Inspect();
  Test("evaluate Test12", res, expected, Printer);
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
}
