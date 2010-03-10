project(Set)
add_library(Set SHARED node.c iterator.c set.c)
target_link_libraries(Set Allocator List Stack)
add_subdirectory(tests)
