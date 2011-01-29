project(ListMapIterator)
cmake_minimum_required(VERSION 2.6)
add_library(ListMapIterator ${Library} code.c)
target_link_libraries(ListMapIterator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory ListMap List Stack ListMapIteratorElement ListMapNode MapIterator Map)