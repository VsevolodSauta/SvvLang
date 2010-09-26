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

Translator putCurrentLevels := method(delta,
	if(delta isNil,
		putNLevels(previousLevel),
		
		putNLevels(previousLevel + delta)
	)
)

Translator putLevel := method(
	while(currentLevel > previousLevel,
		BlockDelegatesHandling blockWillBegin
		putCurrentLevels
		DestinationFile write("{\n")
		previousLevel = previousLevel + 1
		BlockDelegatesHandling blockDidBegin
	)
	while(currentLevel < previousLevel,
		BlockDelegatesHandling blockWillEnd
		previousLevel = previousLevel - 1
		putCurrentLevels()
		DestinationFile write("}\n")
		BlockDelegatesHandling blockDidEnd
	)
	putNLevels(currentLevel)
)

Translator putLine := method(
	if(line tokens ?size == 0, return)
	if(currentLevel == 0,
		if(line tokens at(0) isCreator,
			line translateObjectSignature,
			line translateMethodSignature(true)
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
//		line string println
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
			line translateMethodSignature(false)
		)
	)
	DestinationFile unblockOutput
	TableOfSymbols imported
)

BlockDelegatesHandling init
System args foreach(index, objectClassName,
	if(index == 0, continue)
	Translator beingProcessedObject = objectClassName
	SourceFile openObjectClass(objectClassName)
	DestinationFile openObjectClass(objectClassName)
	
	DestinationFile ignoreBlockingLevelForImport = true
	Translator importObjectType(objectClassName)
	DestinationFile ignoreBlockingLevelForImport = false
	DestinationFile write("#include \"internals/basics.h\"\n")
//	DestinationFile write("#include \"internals/#{Translator beingProcessedObject}/interface.h\"\n" interpolate)
	DestinationFile write("#include \"internals/#{Translator beingProcessedObject}/imports.h\"\n" interpolate)
	DestinationFile write("\n")
	Translator translateMainObject
)
