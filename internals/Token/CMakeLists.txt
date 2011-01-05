project(Token)
cmake_minimum_required(VERSION 2.6)
add_library(Token ${Library} code.c)
target_link_libraries(Token Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable List ListMap)