project(ListNode)
cmake_minimum_required(VERSION 2.6)
add_library(ListNode ${Library} code.c)
target_link_libraries(ListNode Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable )