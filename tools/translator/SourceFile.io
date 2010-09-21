#!/usr/local/bin/io

SourceFile := File clone openForReading(System args at(1))

SourceFile getLine := method(
	Line withString(self readLine)
)
