project(AutoreleasePool)
cmake_minimum_required(VERSION 2.6)
add_library(AutoreleasePool ${Library} code.c)
target_link_libraries(AutoreleasePool Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Stack Console List)