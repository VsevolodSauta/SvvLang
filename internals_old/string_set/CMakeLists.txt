project(StringSet)
cmake_minimum_required(VERSION 2.6)

add_library(StringSet ${Library} node.c element.c iterator.c string_set.c)
target_link_libraries(StringSet Allocator List Stack Char Map)
