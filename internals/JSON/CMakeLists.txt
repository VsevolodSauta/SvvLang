project(JSON)
cmake_minimum_required(VERSION 2.6)
add_library(JSON ${Library} code.c)
target_link_libraries(JSON Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListIterator Char ListMap)