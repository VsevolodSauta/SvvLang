project(ExternalObjectManipulator)
cmake_minimum_required(VERSION 2.6)
add_library(ExternalObjectManipulator ${Library} code.c)
target_link_libraries(ExternalObjectManipulator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListNode ListIterator ListMap Char Map MapIterator ListMapNode Queue Synonim Stack ListMapIteratorElement ListMapIterator UIDGenerator Machine Processor MachineScheduler AutoreleasePool Console)