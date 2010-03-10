project(Queue)
add_library(Queue SHARED queue.c)
target_link_libraries(Queue List Allocator)
add_subdirectory(tests)
