project(Allocator)
cmake_minimum_required(VERSION 2.6)
add_library(Allocator ${Library} allocator.c)
target_link_libraries(Allocator Nothing List)

add_subdirectory(tests)
