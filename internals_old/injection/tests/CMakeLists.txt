project(InjectionTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(InjectionTest${number} test${number}.c)
	target_link_libraries(InjectionTest${number} Injection)
	add_test(NAME Injection_Test_${number} COMMAND InjectionTest${number})
endforeach()
