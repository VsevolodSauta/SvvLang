project(Runtime)
cmake_minimum_required(VERSION 2.6)
add_library(Runtime ${Library} code.c)
target_link_libraries(Runtime Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Undestroyable List ListNode ListIterator Map MapIterator ListMapNode ListMap Queue Synonim Stack ListMapIteratorElement ListMapIterator Char AutoreleasePool Console JSONParser ExternalEntitiesFactory)