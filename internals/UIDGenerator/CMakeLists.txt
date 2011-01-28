project(UIDGenerator)
cmake_minimum_required(VERSION 2.6)
add_library(UIDGenerator ${Library} code.c)
target_link_libraries(UIDGenerator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List)