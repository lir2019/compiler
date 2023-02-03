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
  auto env        = std::make_shared<Environment>();
  auto obj        = Eval(program, env);
  auto res        = obj->Inspect();
  Test(name, res, expected, Printer);
}

static void Test1() {
  std::string input    = R"(
  5;
  )";
  std::string expected = "5";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test1", res, expected, Printer);
}

static void Test2() {
  std::string input    = R"(
  true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test2", res, expected, Printer);
}

static void Test3() {
  std::string input    = R"(
  !true;
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test3", res, expected, Printer);
}

static void Test4() {
  std::string input    = R"(
  !!!!!false;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test4", res, expected, Printer);
}

static void Test5() {
  std::string input    = R"(
  --5;
  )";
  std::string expected = "5";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test5", res, expected, Printer);
}

static void Test6() {
  std::string input    = R"(
  true == true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test6", res, expected, Printer);
}

static void Test7() {
  std::string input    = R"(
  false != true;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test7", res, expected, Printer);
}

static void Test8() {
  std::string input    = R"(
  false == true;
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test8", res, expected, Printer);
}

static void Test9() {
  std::string input    = R"(
  5 < 1 == false;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test9", res, expected, Printer);
}

static void Test10() {
  std::string input    = R"(
  5 - 1 * 4 / 2;
  )";
  std::string expected = "3";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test10", res, expected, Printer);
}

static void Test11() {
  std::string input    = R"(
  5 - 1 * 4 / 2 + 4 * 2 > 9;
  )";
  std::string expected = "true";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test11", res, expected, Printer);
}

static void Test12() {
  std::string input    = R"(
  ((4 - 1) * 2 / (2 + 4) * 2 == 2) == (2 == 3);
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto node = parser.ParseExpression();
  auto env  = std::make_shared<Environment>();
  auto obj  = Eval(*node, env);
  auto res  = obj->Inspect();
  Test("evaluate Test12", res, expected, Printer);
}

static void Test13() {
  std::string input    = R"(
  1 + 1;
  1 + 1 * 2;
  )";
  std::string expected = "3";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test13", res, expected, Printer);
}

static void Test14() {
  std::string input    = R"(
  {
  1 + 1;
  1 + 1 * 2;}
  )";
  std::string expected = "3";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test14", res, expected, Printer);
}

static void Test15() {
  std::string input    = R"(
  1 + if (1 > 2) {12;} else {22;};
  )";
  std::string expected = "23";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test15", res, expected, Printer);
}

static void Test16() {
  std::string input    = R"(
  1 + if (1 < 2) {12;} else {22;} / 2;
  )";
  std::string expected = "7";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test16", res, expected, Printer);
}

static void Test17() {
  std::string input    = R"(
  return 1 + 1;
  )";
  std::string expected = "2";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test17", res, expected, Printer);
}

static void Test18() {
  std::string input    = R"(
  if (10 > 1) {
    if (true != false) {
      return 0;
    };
    return 1;
  };
  )";
  std::string expected = "0";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test18", res, expected, Printer);
}

static void Test19() {
  std::string input    = R"(
  9;
  return 2 * 5;
  11;
  )";
  std::string expected = "10";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test19", res, expected, Printer);
}

static void Test20() {
  std::string input    = R"(
  let a = 5;
  let b = 3;
  let c = a * b;
  c - a;
  )";
  std::string expected = "10";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test20", res, expected, Printer);
}

static void Test21() {
  std::string input    = R"(
  fn(x, y) { return (x + y) / 2; };
  )";
  std::string expected = R"(fn(x, y) {
return ((x + y) / 2);
})";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test21", res, expected, Printer);
}

static void Test22() {
  std::string input    = R"(
  let add = fn(x, y){x + y;};
  add(2 + 2, 5 + 5);
  )";
  std::string expected = "14";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test22", res, expected, Printer);
}

static void Test23() {
  std::string input    = R"(
  let newAdder = fn(x) {
    fn(y) {x+y;};
  };
  let addTwo = newAdder(2);
  addTwo(6);
  )";
  std::string expected = "8";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test23", res, expected, Printer);
}

static void Test24() {
  std::string input    = R"(
  let app = fn(a, b) {return a + b;};
  app("Hello ", "World");
  )";
  std::string expected = "Hello World";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test24", res, expected, Printer);
}

static void Test25() {
  std::string input    = R"(
  let greater = fn(a, b) {return a > b;};
  greater("Hello ", "World");
  )";
  std::string expected = "false";
  Lexer lexer(input);
  Parser parser(lexer);
  auto program = parser.ParseProgram();
  auto env     = std::make_shared<Environment>();
  auto obj     = Eval(program, env);
  auto res     = obj->Inspect();
  Test("evaluate Test25", res, expected, Printer);
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
  Test18();
  Test19();
  Test20();
  Test21();
  Test22();
  Test23();
  Test24();
  Test25();
}
