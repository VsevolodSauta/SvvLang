project(Queue)
cmake_minimum_required(VERSION 2.6)
add_library(Queue ${Library} code.c)
target_link_libraries(Queue Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable List)