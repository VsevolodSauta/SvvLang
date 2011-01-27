project(Runtime)
cmake_minimum_required(VERSION 2.6)
add_library(Runtime ${Library} code.c)
target_link_libraries(Runtime Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory AutoreleasePool Console JSON List ListIterator ListMap)