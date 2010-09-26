project(PairMap)
cmake_minimum_required(VERSION 2.6)

add_library(PairMap ${Library} map.c)
target_link_libraries(PairMap Map)
# add_subdirectory(tests)
