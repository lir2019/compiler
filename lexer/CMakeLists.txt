add_library(lexer lexer.cpp token.cpp)
target_include_directories(lexer PUBLIC "${PROJECT_SOURCE_DIR}")
