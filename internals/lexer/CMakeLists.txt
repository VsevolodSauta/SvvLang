project(Lexer)
cmake_minimum_required(VERSION 2.6)

add_library(Lexer ${Library} lexer.c)
target_link_libraries(Lexer String List Set PairMap StringMap CharFactory)
add_subdirectory(tests)

