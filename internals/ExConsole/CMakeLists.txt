project(ExConsole)
cmake_minimum_required(VERSION 2.6)
add_library(ExConsole ${Library} code.c)
target_link_libraries(ExConsole Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable )