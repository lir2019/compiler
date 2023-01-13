add_library(parser node.cpp)
target_include_directories(lexer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
