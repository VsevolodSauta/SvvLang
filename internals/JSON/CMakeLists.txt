project(JSON)
cmake_minimum_required(VERSION 2.6)
add_library(JSON ${Library} code.c)
target_link_libraries(JSON Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Undestroyable List ListIterator Char ListMap)