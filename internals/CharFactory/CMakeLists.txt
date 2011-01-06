project(CharFactory)
cmake_minimum_required(VERSION 2.6)
add_library(CharFactory ${Library} code.c)
target_link_libraries(CharFactory Object Allocator Number Char)
