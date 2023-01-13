add_library(ast node.cpp program.cpp)
target_include_directories(lexer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
