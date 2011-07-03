project(ThreadManager)
cmake_minimum_required(VERSION 2.6)
add_library(ThreadManager ${Library} code.c)
target_link_libraries(ThreadManager Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Map Thread AutoreleasePool)