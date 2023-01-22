file(GLOB_RECURSE src_files *.cpp *.c)
add_library(object ${src_files})
target_include_directories(object INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
