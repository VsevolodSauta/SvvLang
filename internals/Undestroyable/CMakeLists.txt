project(Undestroyable)
cmake_minimum_required(VERSION 2.6)
add_library(Undestroyable ${Library} code.c)
target_link_libraries(Undestroyable Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console )