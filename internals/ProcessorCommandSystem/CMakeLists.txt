project(ProcessorCommandSystem)
cmake_minimum_required(VERSION 2.6)
add_library(ProcessorCommandSystem ${Library} code.c)
target_link_libraries(ProcessorCommandSystem Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Stack ListMap Processor List Undestroyable Console ListMapIterator Machine)