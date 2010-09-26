project(SetTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 2)
	add_executable(SetTest${number} test${number}.c)
	target_link_libraries(SetTest${number} Set List Allocator)
	add_test(NAME Set_Test_${number} COMMAND SetTest${number})
endforeach()
