project(JSON)
cmake_minimum_required(VERSION 2.6)
add_library(JSON ${Library} code.c)
target_link_libraries(JSON Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable List ListIterator ListMap Char)