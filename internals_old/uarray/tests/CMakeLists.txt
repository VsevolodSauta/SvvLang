project(UArrayTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 1)
	add_executable(UArrayTest${number} test${number}.c)
	target_link_libraries(UArrayTest${number} UArray)
	add_test(NAME UArray_Test_${number} COMMAND UArrayTest${number})
endforeach()
