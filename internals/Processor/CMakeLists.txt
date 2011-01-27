project(Processor)
cmake_minimum_required(VERSION 2.6)
add_library(Processor ${Library} code.c)
target_link_libraries(Processor Object Number Logic Comparation Allocator File Undestroyable Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory ListMap List UIDGenerator MachineScheduler Machine Stack Synonim Console AutoreleasePool ListIterator)