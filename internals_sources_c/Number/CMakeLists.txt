project(Number)
cmake_minimum_required(VERSION 2.6)
add_library(Number ${Library} code.c)
target_link_libraries(Number Object Allocator)
