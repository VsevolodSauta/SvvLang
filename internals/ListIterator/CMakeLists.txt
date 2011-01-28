project(ListIterator)
cmake_minimum_required(VERSION 2.6)
add_library(ListIterator ${Library} code.c)
target_link_libraries(ListIterator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListMap Char)