project(AllocatorTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 1)
	add_executable(AllocatorTest${number} test${number}.c)
	target_link_libraries(AllocatorTest${number} Allocator)
	add_test(NAME Allocator_Test_${number} COMMAND AllocatorTest${number})
endforeach()
