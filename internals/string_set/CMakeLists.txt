project(StringSet)
add_library(StringSet SHARED node.c element.c iterator.c string_set.c)
target_link_libraries(StringSet Allocator List Stack Char Map)