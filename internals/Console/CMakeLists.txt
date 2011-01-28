project(Console)
cmake_minimum_required(VERSION 2.6)
add_library(Console ${Library} code.c)
target_link_libraries(Console Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List)