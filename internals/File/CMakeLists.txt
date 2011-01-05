project(Console)
cmake_minimum_required(VERSION 2.6)
add_library(File ${Library} code.c)
target_link_libraries(File Object Number OSKernel)
