project(ListTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 8)
	add_executable(ListTest${number} test${number}.c)
	target_link_libraries(ListTest${number} List)
	add_test(NAME List_Test_${number} COMMAND ListTest${number})
endforeach()
