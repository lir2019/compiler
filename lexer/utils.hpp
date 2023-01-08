#ifndef LEXER_UTILS_HPP
#define LEXER_UTILS_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#define CHECK(X) do {                                                                         \
  auto res = X;                                                                               \
  if (!res) {                                                                                 \
    std::string ex("check ");                                                                 \
    ex.append(#X);                                                                           \
    ex.append(" failed");                                                                     \
    std::cerr << __FILE__ << ": " << __LINE__  << ex << std::endl;                            \
    throw std::logic_error(ex.c_str());                                                       \
  }                                                                                           \
} while (0)

const std::vector<char> white_space_chars{'\n', ' ', '\t', '\r'};

inline bool IsLetter(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

inline bool IsNumber(char c) {
  return c >= '0' && c <= '9';
}

#endif  // LEXER_UTILS_HPP
