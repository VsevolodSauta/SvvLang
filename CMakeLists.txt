project(SvvLanguage)
cmake_minimum_required(VERSION 2.6)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(Library STATIC)
set(CMAKE_C_FLAGS "-O0 -Wall -g")
enable_testing()

add_subdirectory(internals)
#add_subdirectory(externals)
add_subdirectory(tools)
