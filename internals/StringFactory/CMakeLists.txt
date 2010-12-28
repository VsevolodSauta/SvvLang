project(StringFactory)
cmake_minimum_required(VERSION 2.6)
add_library(StringFactory ${Library} code.c)
target_link_libraries(StringFactory Object Char List Number)

