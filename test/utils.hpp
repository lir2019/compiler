#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <iostream>
#include <functional>

template <typename T>
bool Test(const std::string &name, T out, T expected, void (*print)(T) = nullptr) {
  std::cout << name << " test result: ";
  bool ret = false;
  if (out == expected) {
    std::cout << "success" << std::endl;
    ret = true;
  } else {
    std::cout << "failure" << std::endl;
    ret = false;
    if (print) {
      std::cout << "expected: " << std::endl;
      print(expected);
      std::cout << "but got: " << std::endl;
      print(out);
    }
  }
  return ret;
}

template <typename IN_TYPE, typename OUT_TYPE>
bool Test(const std::string &name, OUT_TYPE (*func)(IN_TYPE), IN_TYPE in, OUT_TYPE expected,
          void (*print)(OUT_TYPE) = nullptr) {
  std::cout << name << " test result: ";
  bool ret = false;
  OUT_TYPE out = func(in);
  if (out == expected) {
    std::cout << "success" << std::endl;
    ret = true;
  } else {
    std::cout << "failure" << std::endl;
    ret = false;
    if (print) {
      std::cout << "expected: " << std::endl;
      print(expected);
      std::cout << "but got: " << std::endl;
      print(out);
    }
  }
  return ret;
}

#endif  //  TEST_UTILS_HPP
