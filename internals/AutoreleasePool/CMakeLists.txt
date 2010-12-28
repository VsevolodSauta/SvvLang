project(AutoreleasePool)
cmake_minimum_required(VERSION 2.6)
add_library(AutoreleasePool ${Library} code.c)
target_link_libraries(AutoreleasePool Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable Stack MultiSet List)