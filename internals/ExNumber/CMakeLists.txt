project(ExNumber)
cmake_minimum_required(VERSION 2.6)
add_library(ExNumber ${Library} code.c)
target_link_libraries(ExNumber Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable )