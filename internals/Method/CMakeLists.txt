project(Method C ASM)
cmake_minimum_required(VERSION 2.6)
add_library(Method ${Library} code.c code.s)
target_link_libraries(Method Object)
