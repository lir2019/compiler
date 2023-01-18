#include "program.hpp"

#include <string>

#include "../common/utils.hpp"

std::string Program::TokenLiteral() const {
  if (stmts_.size() > 0) {
    return stmts_.front()->TokenLiteral();
  }
  return "";
}

DEFINE_DUMP_FUNCS(Program, {
  os << "Program{\n";
  for (auto stmt : stmts_) {
    stmt->PrintNode(os);
    os << "\n";
  }
  os << "}\n";
})

void Program::PrintNode(std::ostream &os) const {
  Print(os);
}
