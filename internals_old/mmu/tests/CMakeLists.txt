project(MMUTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(MMUTest${number} test${number}.c)
	target_link_libraries(MMUTest${number} MMU Allocator)
	add_test(NAME MMU_Test_${number} COMMAND MMUTest${number})
endforeach()
