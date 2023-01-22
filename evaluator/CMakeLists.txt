file(GLOB_RECURSE src_files *.cpp *.c)
add_library(evaluator ${src_files})
target_include_directories(evaluator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
