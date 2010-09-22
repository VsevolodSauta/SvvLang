#!/usr/local/bin/io

SourceFile := File clone

SourceFile openObjectClass := method(objectClassName,
	openForReading("sources/" .. objectClassName .. ".q")
)

SourceFile with := method(objectClassName,
	SourceFile clone openObjectClass(objectClassName)
)

SourceFile getLine := method(
	Line withString(self readLine)
)
