project(Map)
cmake_minimum_required(VERSION 2.6)
add_library(Map ${Library} code.c)
target_link_libraries(Map Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListIterator)