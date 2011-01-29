project(ListMapIteratorElement)
cmake_minimum_required(VERSION 2.6)
add_library(ListMapIteratorElement ${Library} code.c)
target_link_libraries(ListMapIteratorElement Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory ListMapNode MapIterator)