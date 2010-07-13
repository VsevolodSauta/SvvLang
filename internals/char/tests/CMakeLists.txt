project(CharTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 2)
	add_executable(CharTest${number} test${number}.c)
	target_link_libraries(CharTest${number} Char CharFactory)
	add_test(NAME Char_Test_${number} COMMAND CharTest${number})
endforeach()
