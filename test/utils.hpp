#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>

template <typename T1, typename T2>
bool Test(const std::string &name, T1 out, T2 expected) {
  std::cout << name << " test result: ";
  if (out == expected) {
    std::cout << "success" << std::endl;
    return true;
  } else {
    std::cout << "failure" << std::endl;
    return false;
  }
  return false;
}

template <typename T1, typename T2>
bool Test(const std::string &name, T2 (*func)(T1), T1 in, T2 expected) {
  T2 out = func(in);
  return Test(name, out, expected);
}

#endif  //  TEST_UTILS_HPP
