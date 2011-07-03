project(Machine)
cmake_minimum_required(VERSION 2.6)
add_library(Machine ${Library} code.c)
target_link_libraries(Machine Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory ListMap UIDGenerator Processor List MachineScheduler ExternalMachineManipulator ExternalActorsFactory ThreadManager AutoreleasePool Console JSONParser ListIterator Undestroyable ListMapIterator Synonim)