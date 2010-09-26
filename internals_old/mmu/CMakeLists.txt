project(MMU)
cmake_minimum_required(VERSION 2.6)

add_library(MMU ${Library} mmu.c)
add_subdirectory(tests)
