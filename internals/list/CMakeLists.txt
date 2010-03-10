project(List)
add_library(List ${Library} node.c iterator.c list.c)
target_link_libraries(List Allocator MMU Object)

add_subdirectory(tests)
