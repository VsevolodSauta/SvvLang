project(NumberTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(NumberTest${number} test${number}.c)
	target_link_libraries(NumberTest${number} Number Allocator Object NumberFactory)
	add_test(NAME Number_Test_${number} COMMAND NumberTest${number})
endforeach()
