project(List)
cmake_minimum_required(VERSION 2.6)

add_library(List ${Library} node.c iterator.c list.c)
target_link_libraries(List Allocator Object Number NumberFactory Logic Comparison Nothing)

add_subdirectory(tests)
