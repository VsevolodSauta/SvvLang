project(OSKernel ASM)
cmake_minimum_required(VERSION 2.6)
add_library(OSKernel ${Library} linux.s)
#set_target_properties(OSKernel PROPERTIES LINKER_LANGUAGE ASM)
