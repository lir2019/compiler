#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <iostream>
#include <memory>

#define LOG do { std::cout << __FILE__ << ": " << __LINE__ << std::endl; } while (false)

#define CHECK(predicate, comment) do {                                                        \
  auto res = predicate;                                                                       \
  if (!res) {                                                                                 \
    std::string ex("check ");                                                                 \
    ex.append(#predicate);                                                                    \
    ex.append(" failed");                                                                     \
    std::cerr << __FILE__ << ": " << __LINE__ << " " << ex << ": " << #comment << std::endl;  \
    throw std::runtime_error(ex.c_str());                                                     \
  }                                                                                           \
} while (0)

template <typename T, typename First>
bool IsA(std::shared_ptr<T> sptr) {
  if (sptr == nullptr) {
    return false;
  }
  if (std::dynamic_pointer_cast<First>(sptr)) {
    return true;
  }
  return false;
}

template <typename T, typename First, typename Second, typename ...Rest>
bool IsA(std::shared_ptr<T> sptr) {
  if (sptr == nullptr) {
    return false;
  }
  if (std::dynamic_pointer_cast<First>(sptr)) {
    return true;
  }
  return IsA<T, Second, Rest...>(sptr);
}

#endif  // COMMON_UTILS_HPP
