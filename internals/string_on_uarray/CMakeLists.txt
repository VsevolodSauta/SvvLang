project(String)
cmake_minimum_required(VERSION 2.6)

add_library(String ${Library} iterator.c string.c)
target_link_libraries(String Allocator UArray Char)
add_subdirectory(tests)
