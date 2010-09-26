project(ListTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 7)
	add_executable(ListTest${number} test${number}.c)
	target_link_libraries(ListTest${number} List Number Allocator Object NumberFactory)
	add_test(NAME List_Test_${number} COMMAND ListTest${number})
endforeach()
