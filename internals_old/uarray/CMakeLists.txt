project(UArray)
cmake_minimum_required(VERSION 2.6)

add_library(UArray ${Library} uarray.c)
target_link_libraries(UArray Allocator MMU Object)

add_subdirectory(tests)
