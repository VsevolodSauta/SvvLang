project(MultiSet)
cmake_minimum_required(VERSION 2.6)
add_library(MultiSet ${Library} code.c)
target_link_libraries(MultiSet Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable List)