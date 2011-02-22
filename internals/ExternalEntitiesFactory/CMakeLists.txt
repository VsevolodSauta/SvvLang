project(ExternalEntitiesFactory)
cmake_minimum_required(VERSION 2.6)
add_library(ExternalEntitiesFactory ${Library} code.c)
target_link_libraries(ExternalEntitiesFactory Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator ListMap Char Map MapIterator ListMapNode Queue Synonim Stack ListMapIteratorElement ListMapIterator)