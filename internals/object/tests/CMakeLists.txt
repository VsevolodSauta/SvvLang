project(ObjectTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 1)
	add_executable(ObjectTest${number} test${number}.c)
	target_link_libraries(ObjectTest${number} Object)
	add_test(NAME Object_Test_${number} COMMAND ObjectTest${number})
endforeach()
