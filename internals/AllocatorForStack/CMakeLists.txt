project(AllocatorForStack)
cmake_minimum_required(VERSION 2.6)
add_library(AllocatorForStack ${Library} code.c)
target_link_libraries(AllocatorForStack Undestroyable OSKernel)
