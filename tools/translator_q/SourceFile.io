#!/usr/local/bin/io

SourceFile := File clone
SourceFile lineNumber := 0

SourceFile clone := method(
	toReturn := super(clone)
	toReturn lineNumber := 0
	toReturn
)

SourceFile openObjectClass := method(objectClassName,
	openForReading("../../internals_sources_q/#{objectClassName}.q" interpolate)
)

SourceFile with := method(objectClassName,
	SourceFile clone openObjectClass(objectClassName)
)

SourceFile getLine := method(
	lineNumber = lineNumber + 1
	Line withStringAndNumber(self readLine, lineNumber)
)
