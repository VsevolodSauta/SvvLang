project(Allocator)
cmake_minimum_required(VERSION 2.6)
add_library(Allocator ${Library} code.c)
target_link_libraries(Allocator Undestroyable OSKernel HardwareSpecific)
