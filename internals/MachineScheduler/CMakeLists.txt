project(MachineScheduler)
cmake_minimum_required(VERSION 2.6)
add_library(MachineScheduler ${Library} code.c)
target_link_libraries(MachineScheduler Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Queue List)