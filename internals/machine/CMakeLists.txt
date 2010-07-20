project(Machine)
cmake_minimum_required(VERSION 2.6)

add_library(Machine ${Library} machine.c)
target_link_libraries(Machine Lexer List Allocator ExternalObject ExternalMachine StringFactory)
# add_subdirectory(tests)
