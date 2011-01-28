project(Stack)
cmake_minimum_required(VERSION 2.6)
add_library(Stack ${Library} code.c)
target_link_libraries(Stack Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List)