project(AutoreleasePool)
cmake_minimum_required(VERSION 2.6)
add_library(AutoreleasePool ${Library} code.c)
target_link_libraries(AutoreleasePool Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable Stack Console MultiSet List)