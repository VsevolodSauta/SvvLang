project(MultiSet)
cmake_minimum_required(VERSION 2.6)
add_library(MultiSet ${Library} code.c)
target_link_libraries(MultiSet Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List)