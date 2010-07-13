project(LexerTests)
cmake_minimum_required(VERSION 2.6)

foreach(number RANGE 0)
	add_executable(LexerTest${number} test${number}.c)
	target_link_libraries(LexerTest${number} Lexer CharFactory String List)
	add_test(NAME Lexer_Test_${number} COMMAND LexerTest${number})
endforeach()
