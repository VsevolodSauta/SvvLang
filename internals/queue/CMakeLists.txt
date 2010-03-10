project(Queue)
add_library(Queue ${Library} queue.c)
target_link_libraries(Queue List Allocator)
add_subdirectory(tests)
