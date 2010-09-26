project(AutoreleasePool)
cmake_minimum_required(VERSION 2.6)
add_library(AutoreleasePool ${Library} autorelease_pool.c)
target_link_libraries(AutoreleasePool Nothing List)

# add_subdirectory(tests)
