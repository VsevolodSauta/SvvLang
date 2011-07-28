project(Object)
cmake_minimum_required(VERSION 2.6)
add_library(Object ${Library} code.c)
target_link_libraries(Object Allocator AutoreleasePool)
