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

int main() {
}
