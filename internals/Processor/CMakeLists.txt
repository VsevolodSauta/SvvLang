project(Processor)
cmake_minimum_required(VERSION 2.6)
add_library(Processor ${Library} code.c)
target_link_libraries(Processor Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator ListMap Char Map ListMapNode Queue Synonim UIDGenerator MachineScheduler Machine Stack Console AutoreleasePool)