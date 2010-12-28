project(Array)
cmake_minimum_required(VERSION 2.6)
add_library(Array ${Library} code.c)
target_link_libraries(Array Object Allocator)
