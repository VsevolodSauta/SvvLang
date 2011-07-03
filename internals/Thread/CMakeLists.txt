project(Thread)
cmake_minimum_required(VERSION 2.6)
add_library(Thread ${Library} code.c)
target_link_libraries(Thread Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory AutoreleasePool)