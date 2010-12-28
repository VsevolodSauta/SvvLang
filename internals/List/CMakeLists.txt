project(List)
cmake_minimum_required(VERSION 2.6)
add_library(List ${Library} code.c)
target_link_libraries(List Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable ListIterator ListNode)