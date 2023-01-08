#include <iostream>

#include "test/utils.hpp"

template <typename T>
T Abs(T in) {
  return in < 0 ? -in : in;
}

int main() {
  Test("case1", Abs, -2.0, 2.0);
  Test("case2", Abs, 3.0, 3.0);
}
