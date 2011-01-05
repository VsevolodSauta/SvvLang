project(Runtime)
cmake_minimum_required(VERSION 2.6)
add_library(Runtime ${Library} code.c)
target_link_libraries(Runtime Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable List ListNode ListIterator Map ListMapNode ListMap Queue Synonim Stack AutoreleasePool Console)