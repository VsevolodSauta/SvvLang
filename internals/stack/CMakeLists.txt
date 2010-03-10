project(Stack)
add_library(Stack ${Library} stack.c)
target_link_libraries(Stack List Allocator)
add_subdirectory(tests)

