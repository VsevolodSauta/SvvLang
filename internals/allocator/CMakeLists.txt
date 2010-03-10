project(Allocator)
cmake_minimum_required(VERSION 2.6)
add_library(Allocator ${Library} allocator.c)

add_subdirectory(tests)
