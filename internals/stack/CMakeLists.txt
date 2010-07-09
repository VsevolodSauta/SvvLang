project(Stack)
cmake_minimum_required(VERSION 2.6)

add_library(Stack ${Library} stack.c)
target_link_libraries(Stack List Allocator)
add_subdirectory(tests)

