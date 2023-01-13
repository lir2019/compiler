#include "parser.hpp"

Parser::NextToken() {
  cur_tok_ = next_tok_;
  next_tok_ = lex_->NextToken();
}
