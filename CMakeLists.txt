cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(MonkeyCompiler VERSION 0.1)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
message(PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}")

add_subdirectory(lexer)
add_subdirectory(ast)
add_subdirectory(parser)

configure_file(MonkeyCompilerConfig.h.in MonkeyCompilerConfig.h)

add_executable(test_configure_file test/cmake/main.cpp)
target_include_directories(test_configure_file PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")

add_executable(test_lexer test/lexer/main.cpp)
target_include_directories(test_lexer PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(test_lexer PUBLIC lexer)

enable_testing()
add_test(NAME TestCMakeConfig COMMAND test_configure_file)
set_tests_properties(TestCMakeConfig PROPERTIES PASS_REGULAR_EXPRESSION "success.*success")

function(do_lexer_test arg)
  add_test(NAME TestLexerCase${arg} COMMAND test_lexer ${arg})
  set_tests_properties(TestLexerCase${arg} PROPERTIES PASS_REGULAR_EXPRESSION "success" FAIL_REGULAR_EXPRESSION "failure")
endfunction()

do_lexer_test(1)
do_lexer_test(2)
do_lexer_test(3)
do_lexer_test(4)
do_lexer_test(5)
do_lexer_test(6)
