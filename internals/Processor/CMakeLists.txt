project(Processor)
cmake_minimum_required(VERSION 2.6)
add_library(Processor ${Library} code.c)
target_link_libraries(Processor Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory Console Undestroyable ListMap List UIDGenerator MachineScheduler Machine Stack Synonim Queue AutoreleasePool ListIterator)