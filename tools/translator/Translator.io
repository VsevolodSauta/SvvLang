#!/usr/local/bin/io

Translator := Object clone
Translator previousLevel := 0
Translator currentLevel := 0
Translator line := nil

Translator putNLevels := method(n,
	n repeat(
		DestinationFile write("\t")
	)
)

Translator putLevel := method(
	if(currentLevel > previousLevel,
		TableOfSymbols pushFrame
		putNLevels(previousLevel)
		DestinationFile write("{\n")
		previousLevel = currentLevel
	)
	if(currentLevel < previousLevel,
		TableOfSymbols popFrame
		putNLevels(currentLevel)
		DestinationFile write("}\n")
		previousLevel = currentLevel
	)
	putNLevels(currentLevel)
)

Translator putLine := method(
	if(line tokens ?size == 0, return)
	if(currentLevel == 0,
		line translateMethodSignature,
		line translateMethodEntryLine
	)
)

Translator insertDeclaration := method(name,
	DestinationFile write("Object #{name};\n" interpolate)
	putLevel
)

TableOfSymbols pushFrame
loop(
	Translator line = SourceFile getLine
	if(Translator line isNil, break)
	Translator currentLevel = Translator line getLevel
	Translator putLevel
	Translator putLine
	DestinationFile write("\n")
)
