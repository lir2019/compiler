#ifndef PARSER_PROGRAM_HPP
#define PARSER_PROGRAM_HPP

#include <vector>
#include <memory>

#include "node.hpp"

class Program : public INode {
public:
  Program() {}

  virtual std::string TokenLiteral() override;

  void AppendStmt(std::shared_ptr<IStatement> s) {
    stmts_.push_back(s);
  }

  std::vector<std::shared_ptr<IStatement>> GetStmts() const {
    return stmts_;
  }

  std::shared_ptr<IStatement> GetStmt(int64_t idx) const {
    if (idx < 0 || idx >= stmts_.size()) {
      throw;
    }
    return stmts_[idx];
  }
private:
  std::vector<std::shared_ptr<IStatement>> stmts_;
};

#endif  // PARSER_PROGRAM_HPP
