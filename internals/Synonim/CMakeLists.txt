project(Synonim)
cmake_minimum_required(VERSION 2.6)
add_library(Synonim ${Library} code.c)
target_link_libraries(Synonim Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable List ListIterator ListMap)