project(String)
add_library(String SHARED iterator.c string.c)
target_link_libraries(String Allocator List Char)
# add_subdirectory(tests)