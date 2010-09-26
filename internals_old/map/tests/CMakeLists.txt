project(MapTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(MapTest${number} test${number}.c)
	target_link_libraries(MapTest${number} Map)
	add_test(NAME Map_Test_${number} COMMAND MapTest${number})
endforeach()
