project(Console)
cmake_minimum_required(VERSION 2.6)
add_library(Console ${Library} code.c)
target_link_libraries(Console Object Number)
