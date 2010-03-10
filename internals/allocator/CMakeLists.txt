project(Allocator)
cmake_minimum_required(VERSION 2.6)
add_library(Allocator SHARED allocator.c)

add_subdirectory(tests)
