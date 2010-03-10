project(String)
add_library(String ${Library} iterator.c string.c)
target_link_libraries(String Allocator List Char)
# add_subdirectory(tests)