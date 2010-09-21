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
	while(currentLevel > previousLevel,
		if(previousLevel != 0, 
			TableOfSymbols pushFrame
		)
		putNLevels(previousLevel)
		DestinationFile write("{\n")
		previousLevel = previousLevel + 1
	)
	while(currentLevel < previousLevel,
		TableOfSymbols popFrame
		previousLevel = previousLevel - 1
		putNLevels(previousLevel)
		DestinationFile write("}\n")
	)
	putNLevels(currentLevel)
)

Translator putLine := method(
	if(line tokens ?size == 0, return)
	if(currentLevel == 0,
		if(line tokens at(0) isCreator,
			line translateObjectSignature,
			line translateMethodSignature
		),
		
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
