project(Set)
cmake_minimum_required(VERSION 2.6)

add_library(Set ${Library} node.c iterator.c set.c)
target_link_libraries(Set Allocator List Stack)
add_subdirectory(tests)
