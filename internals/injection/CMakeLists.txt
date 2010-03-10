project(Injection)
add_library(Injection ${Library} node.c iterator.c injection.c)
target_link_libraries(Injection List Allocator Stack Object)
add_subdirectory(tests)