project(ListMapNode)
cmake_minimum_required(VERSION 2.6)
add_library(ListMapNode ${Library} code.c)
target_link_libraries(ListMapNode Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Map List ListIterator Char)