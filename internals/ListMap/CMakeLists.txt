project(ListMap)
cmake_minimum_required(VERSION 2.6)
add_library(ListMap ${Library} code.c)
target_link_libraries(ListMap Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator Char Map MapIterator ListMapNode Queue Synonim Stack ListMapIteratorElement ListMapIterator Console ExternalEntitiesFactory)