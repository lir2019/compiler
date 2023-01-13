#include "program.hpp"

#include <string>

std::string Program::TokenLiteral() {
  if (stmts_.size() > 0) {
    return stmts_.front()->TokenLiteral();
  }
  return "";
}

