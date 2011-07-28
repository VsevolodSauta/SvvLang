project(SimpleNumber)
cmake_minimum_required(VERSION 2.6)
add_library(SimpleNumber ${Library} code.c)
target_link_libraries(SimpleNumber Object Allocator)
