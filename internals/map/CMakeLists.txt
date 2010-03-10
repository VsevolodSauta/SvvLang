project(Map)
add_library(Map ${Library} node.c iterator.c map.c)
target_link_libraries(Map List Allocator Stack Object)
add_subdirectory(tests)