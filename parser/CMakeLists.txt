file(GLOB_RECURSE src_files *.cpp *.c)
add_library(parser ${src_files})
target_include_directories(parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
