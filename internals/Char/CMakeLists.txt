project(Char)
cmake_minimum_required(VERSION 2.6)
add_library(Char ${Library} code.c)
target_link_libraries(Char Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory )