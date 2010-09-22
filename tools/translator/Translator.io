#!/usr/local/bin/io

Translator := Object clone
Translator previousLevel := 0
Translator currentLevel := 0
Translator line := nil
Translator beingProcessedObject := Sequence clone
Translator beingProcessedObject = System args at(1)

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

Translator translateMainObject := method(
	TableOfSymbols pushFrame
	loop(
		line = SourceFile getLine
		if(line isNil, break)
		currentLevel = line getLevel
		putLevel
		putLine
		DestinationFile write("\n")
	)
)

Translator importObjectType := method(objectName,
	if(TableOfSymbols importing(objectName), return)
	DestinationFile addImport(objectName)
	DestinationFile blockOutput
	TableOfSymbols import(objectName)
	fileToImport := SourceFile with(objectName)
	loop(
		line := fileToImport getLine
		if(line isNil, break)
		currentLevel := line getLevel
		if(line tokens ?size == 0, continue)
		if(currentLevel != 0, continue)
		if(line tokens at(0) isCreator,
			line translateObjectSignature,
			line translateMethodSignature
		)
	)
	DestinationFile unblockOutput
	TableOfSymbols imported
)

System args foreach(index, objectClassName,
	if(index == 0, continue)
	Translator beingProcessedObject = objectClassName
	SourceFile openObjectClass(objectClassName)
	DestinationFile openObjectClass(objectClassName)
	
	DestinationFile write("#include \"internals/basics.h\"\n")
	DestinationFile write("#include \"internals/#{Translator beingProcessedObject}/interface.h\"\n" interpolate)
	DestinationFile write("#include \"internals/#{Translator beingProcessedObject}/imports.h\"\n" interpolate)
	DestinationFile write("\n")
	Translator translateMainObject
)