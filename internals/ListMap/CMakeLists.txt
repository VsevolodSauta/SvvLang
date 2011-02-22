project(ListMap)
cmake_minimum_required(VERSION 2.6)
add_library(ListMap ${Library} code.c)
target_link_libraries(ListMap Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory ListMapNode Map List ListIterator Stack Undestroyable Queue Synonim ListMapIterator Console ExternalEntitiesFactory)