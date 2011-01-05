project(Machine)
cmake_minimum_required(VERSION 2.6)
add_library(Machine ${Library} code.c)
target_link_libraries(Machine Object Number Logic Comparation Allocator NumberFactory LogicFactory StringFactory File Undestroyable ListMap UIDGenerator Processor MachineScheduler AutoreleasePool Console List Queue)