project(NumberFactory)
cmake_minimum_required(VERSION 2.6)
add_library(NumberFactory ${Library} code.c)
target_link_libraries(NumberFactory Object Allocator Number)
