project(MapIterator)
cmake_minimum_required(VERSION 2.6)
add_library(MapIterator ${Library} code.c)
target_link_libraries(MapIterator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator Map ListMapNode ListMap Queue Synonim Stack ListMapIteratorElement ListMapIterator Char)