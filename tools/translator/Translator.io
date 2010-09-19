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
		putNLevels(previousLevel)
		DestinationFile write("{\n")
		previousLevel = currentLevel
	)
	if(currentLevel < previousLevel,
		putNLevels(currentLevel)
		DestinationFile write("}\n")
		previousLevel = currentLevel
	)
	putNLevels(currentLevel)
)

Translator putLine := method(
	if(line tokens ?size == 0, return)
	if(currentLevel == 0,
		line putMethodSignature,
		line putMethodEntryLine
	)
)

loop(
	if(SourceFile isAtEnd, break)
	Translator line = SourceFile getLine
	Translator currentLevel = Translator line getLevel
	Translator putLevel
	Translator putLine
	DestinationFile write("\n")
)