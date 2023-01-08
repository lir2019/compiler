#include <iostream>

#include "test/utils.hpp"
#include "MonkeyCompilerConfig.h"

int main() {
  Test("test cmake VERSION_MAJOR", MonkeyCompiler_VERSION_MAJOR, 0);
  Test("test cmake VERSION_MINOR", MonkeyCompiler_VERSION_MINOR, 1);
}
