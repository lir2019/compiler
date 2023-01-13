cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(MonkeyCompiler VERSION 0.1)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
message(PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}")

configure_file(MonkeyCompilerConfig.h.in MonkeyCompilerConfig.h)

add_executable(test_configure_file test/cmake/main.cpp)
target_include_directories(test_configure_file PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")

add_subdirectory(lexer)

add_executable(test_lexer test/lexer/main.cpp)
target_include_directories(test_lexer PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(test_lexer PUBLIC lexer)
