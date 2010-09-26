project(QueueTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(QueueTest${number} test${number}.c)
	target_link_libraries(QueueTest${number} Queue)
	add_test(NAME Queue_Test_${number} COMMAND QueueTest${number})
endforeach()
