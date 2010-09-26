project(AutoreleasePoolsStack)
cmake_minimum_required(VERSION 2.6)
add_library(AutoreleasePoolsStack ${Library} autorelease_pools_stack.c)
target_link_libraries(AutoreleasePoolsStack Stack Object)

# add_subdirectory(tests)
