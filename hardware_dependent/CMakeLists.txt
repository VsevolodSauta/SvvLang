project(HardwareSpecific ASM)
cmake_minimum_required(VERSION 2.6)
add_library(HardwareSpecific ${Library} amd64.s)
