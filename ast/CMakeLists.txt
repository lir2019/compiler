file(GLOB_RECURSE src_files *.cpp *.c)
add_library(ast ${src_files})
target_include_directories(ast INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
