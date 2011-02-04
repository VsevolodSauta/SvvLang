project(Processor)
cmake_minimum_required(VERSION 2.6)
add_library(Processor ${Library} code.c)
target_link_libraries(Processor Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory List ListMap UIDGenerator MachineScheduler Machine ExternalObjectManipulator Stack Synonim Console ListMapIterator AutoreleasePool ListIterator)