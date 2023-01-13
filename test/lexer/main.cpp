#include <string>
#include <vector>
#include <functional>

#include "common/utils.hpp"
#include "test/utils.hpp"
#include "lexer/token.hpp"
#include "lexer/lexer.hpp"

static void Printer(std::vector<Token> ts) {
  for (auto t : ts) {
    std::cout << t << std::endl;
  }
}

static void Test1() {
  std::string input;

  std::vector<Token> expected{
    Token{TokenType::END, ""}
  };

  Test("empty input", StrToTokens, input, expected);
}

static void Test2() {
  std::string input = "\n";

  std::vector<Token> expected{
    Token{TokenType::END, ""}
  };

  Test("all whitespace input1", StrToTokens, input, expected);
}

static void Test3() {
  std::string input = "\t\n \r";

  std::vector<Token> expected{
    Token{TokenType::END, ""}
  };

  Test("all whitespace input2", StrToTokens, input, expected);
}

static void Test4() {
  std::string input = R"(
=;(),+{}
)";

  std::vector<Token> expected{
    Token{TokenType::ASSIGN, "="},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::LPAREN, "("},
    Token{TokenType::RPAREN, ")"},
    Token{TokenType::COMMA, ","},
    Token{TokenType::PLUS, "+"},
    Token{TokenType::LBRACE, "{"},
    Token{TokenType::RBRACE, "}"},
    Token{TokenType::END, ""}
  };

  Test("signs input", StrToTokens, input, expected);
}

static void Test5() {
  std::string input = R"(let five = 5;
let ten = 10;
let add = fn(x, y) {
  x + y;
};
let result = add(five, ten);
)";

  std::vector<Token> expected{
    Token{TokenType::LET, "let"},
    Token{TokenType::IDENT, "five"},
    Token{TokenType::ASSIGN, "="},
    Token{TokenType::INT, "5"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::LET, "let"},
    Token{TokenType::IDENT, "ten"},
    Token{TokenType::ASSIGN, "="},
    Token{TokenType::INT, "10"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::LET, "let"},
    Token{TokenType::IDENT, "add"},
    Token{TokenType::ASSIGN, "="},
    Token{TokenType::FUNCTION, "fn"},
    Token{TokenType::LPAREN, "("},
    Token{TokenType::IDENT, "x"},
    Token{TokenType::COMMA, ","},
    Token{TokenType::IDENT, "y"},
    Token{TokenType::RPAREN, ")"},
    Token{TokenType::LBRACE, "{"},
    Token{TokenType::IDENT, "x"},
    Token{TokenType::PLUS, "+"},
    Token{TokenType::IDENT, "y"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::RBRACE, "}"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::LET, "let"},
    Token{TokenType::IDENT, "result"},
    Token{TokenType::ASSIGN, "="},
    Token{TokenType::IDENT, "add"},
    Token{TokenType::LPAREN, "("},
    Token{TokenType::IDENT, "five"},
    Token{TokenType::COMMA, ","},
    Token{TokenType::IDENT, "ten"},
    Token{TokenType::RPAREN, ")"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::END, ""}
  };

  Test("case1", StrToTokens, input, expected, Printer);
}

static void Test6() {
  std::string input = R"(!-/*5;
5 < 10 > 5;
if (5 < 10) {
  return true;
} else {
  return false;
}
10 == 10;
10 != 9;
)";

  std::vector<Token> expected{
    Token{TokenType::BANG, "!"},
    Token{TokenType::MINUS, "-"},
    Token{TokenType::SLASH, "/"},
    Token{TokenType::ASTERISK, "*"},
    Token{TokenType::INT, "5"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::INT, "5"},
    Token{TokenType::LT, "<"},
    Token{TokenType::INT, "10"},
    Token{TokenType::GT, ">"},
    Token{TokenType::INT, "5"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::IF, "if"},
    Token{TokenType::LPAREN, "("},
    Token{TokenType::INT, "5"},
    Token{TokenType::LT, "<"},
    Token{TokenType::INT, "10"},
    Token{TokenType::RPAREN, ")"},
    Token{TokenType::LBRACE, "{"},
    Token{TokenType::RETURN, "return"},
    Token{TokenType::TRUE, "true"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::RBRACE, "}"},
    Token{TokenType::ELSE, "else"},
    Token{TokenType::LBRACE, "{"},
    Token{TokenType::RETURN, "return"},
    Token{TokenType::FALSE, "false"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::RBRACE, "}"},
    Token{TokenType::INT, "10"},
    Token{TokenType::EQ, "=="},
    Token{TokenType::INT, "10"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::INT, "10"},
    Token{TokenType::NE, "!="},
    Token{TokenType::INT, "9"},
    Token{TokenType::SEMICOLON, ";"},
    Token{TokenType::END, ""},
  };

  Test("case2", StrToTokens, input, expected, Printer);
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }
  std::string num_str(argv[1]);
  int num = std::stoi(num_str);
  switch (num) {
    case 1: Test1(); break;
    case 2: Test2(); break;
    case 3: Test3(); break;
    case 4: Test4(); break;
    case 5: Test5(); break;
    case 6: Test6(); break;
    default: break;
  }
  return 0;
}
