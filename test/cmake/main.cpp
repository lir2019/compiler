#include <iostream>

#include "common/utils.hpp"
#include "test/utils.hpp"
#include "MonkeyCompilerConfig.h"

int main() {
  LOG;
  Test("cmake VERSION_MAJOR", MonkeyCompiler_VERSION_MAJOR, 0);
  Test("cmake VERSION_MINOR", MonkeyCompiler_VERSION_MINOR, 1);
  LOG;
}
