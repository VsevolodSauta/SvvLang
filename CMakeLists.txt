project(SvvLanguage)
cmake_minimum_required(VERSION 2.6)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(Library STATIC)
set(CMAKE_C_FLAGS "-O0 -g -Wall -nostdlib -fno-builtin -std=gnu99 -fms-extensions")
enable_testing()

add_subdirectory(hardware_dependent)
add_subdirectory(os_dependent)
add_subdirectory(internals)
#add_subdirectory(externals)
#add_subdirectory(tools)
