project(Machine)
cmake_minimum_required(VERSION 2.6)
add_library(Machine ${Library} code.c)
target_link_libraries(Machine Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator ListMap Char Map ListMapNode Queue Synonim UIDGenerator Stack Processor MachineScheduler AutoreleasePool Console JSON)