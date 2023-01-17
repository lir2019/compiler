file(GLOB_RECURSE src_files *.cpp *.c)
add_library(lexer ${src_files})
target_include_directories(lexer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
