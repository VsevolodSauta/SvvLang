project(MethodFactory)
cmake_minimum_required(VERSION 2.6)
add_library(MethodFactory ${Library} code.c)
target_link_libraries(MethodFactory Object Allocator Method)
