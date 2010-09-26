project(TokenFactory)
cmake_minimum_required(VERSION 2.6)

add_library(TokenFactory ${Library} token_factory.c)
target_link_libraries(TokenFactory StringFactory StringMap PairMap)
#add_subdirectory(tests)

