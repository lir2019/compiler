#include "program.hpp"

#include <string>

std::string Program::TokenLiteral() const {
  if (stmts_.size() > 0) {
    return stmts_.front()->TokenLiteral();
  }
  return "";
}

void Program::Print(std::ostream &os) const {
  os << "Program(\n";
  for (auto stmt : stmts_) {
    stmt->Print(os);
    os << "\n";
  }
  os << ")\n";
}

std::ostream &operator<<(std::ostream &os, const Program &program) {
  program.Print(os);
  return os;
}
