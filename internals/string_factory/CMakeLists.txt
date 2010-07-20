project(StringFactory)
cmake_minimum_required(VERSION 2.6)

add_library(StringFactory ${Library} string_factory.c)
target_link_libraries(StringFactory Char String)

# add_subdirectory(tests)
