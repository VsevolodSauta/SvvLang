project(StringMap)
cmake_minimum_required(VERSION 2.6)

add_library(StringMap ${Library} node.c element.c iterator.c string_map.c)
target_link_libraries(StringMap Allocator List Stack Char Map)
