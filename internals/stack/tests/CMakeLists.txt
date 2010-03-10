project(StackTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(StackTest${number} test${number}.c)
	target_link_libraries(StackTest${number} Stack)
	add_test(NAME Stack_Test_${number} COMMAND StackTest${number})
endforeach()
