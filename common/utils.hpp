#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <iostream>

#define LOG do { std::cout << __FILE__ << ": " << __LINE__ << std::endl; } while (false)

template <typename T, typename First>
bool IsA(std::shared_ptr<T> sptr) {
  if (dynamic_cast<First *>(sptr.get())) {
    return true;
  }
  return false;
}

template <typename T, typename First, typename Second, typename ...Rest>
bool IsA(std::shared_ptr<T> sptr) {
  if (dynamic_cast<First *>(sptr.get())) {
    return true;
  }
  return IsA<T, Second, Rest...>(sptr);
}

#endif  // COMMON_UTILS_HPP
