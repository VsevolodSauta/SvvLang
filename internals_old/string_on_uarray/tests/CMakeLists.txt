project(StringTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 3)
	add_executable(StringTest${number} test${number}.c)
	target_link_libraries(StringTest${number} String)
	add_test(NAME String_Test_${number} COMMAND StringTest${number})
endforeach()
