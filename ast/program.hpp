#ifndef PARSER_PROGRAM_HPP
#define PARSER_PROGRAM_HPP

#include <vector>
#include <memory>

#include "../common/utils.hpp"
#include "node.hpp"
#include "statement.hpp"

class Program : public INode {
public:
  Program() {}

  DECL_DUMP_FUNCS(Program)

  virtual std::string TokenLiteral() const override;
  virtual void PrintNode(std::ostream &os) const override;

  void AppendStmt(std::shared_ptr<IStatement> s) {
    stmts_.push_back(s);
  }

  std::vector<std::shared_ptr<IStatement>> GetStmts() const {
    return stmts_;
  }

  std::shared_ptr<IStatement> GetStmt(int64_t idx) const {
    CHECK(idx < 0 || idx >= stmts_.size(), "index out of range");
    return stmts_[idx];
  }
private:
  std::vector<std::shared_ptr<IStatement>> stmts_;
};

#endif  // PARSER_PROGRAM_HPP
