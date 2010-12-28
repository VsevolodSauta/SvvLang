project(ExObject)
cmake_minimum_required(VERSION 2.6)
add_library(ExObject ${Library} code.c)
target_link_libraries(ExObject Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable )