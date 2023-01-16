#ifndef LEXER_UTILS_HPP
#define LEXER_UTILS_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

const std::vector<char> white_space_chars{'\n', ' ', '\t', '\r'};

inline bool IsLetter(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

inline bool IsNumber(char c) {
  return c >= '0' && c <= '9';
}

#endif  // LEXER_UTILS_HPP
