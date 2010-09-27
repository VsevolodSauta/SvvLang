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

Translator blockDidBegin := method(
	putCurrentLevels
	DestinationFile write("{\n")
	previousLevel = previousLevel + 1
	BlockDelegatesHandling afterEachBlockBegins(Translator, 5)
	BlockDelegatesHandling afterBlockEnds(Translator, 0)
)

Translator blockDidEnd := method(
	previousLevel = previousLevel - 1
	putCurrentLevels
	DestinationFile write("}\n")
)

Translator putLevel := method(
	if((currentLevel == 0) and (Translator line ?tokens ?size != 0),
		if(line tokens first isCreator not,
			BlockDelegatesHandling blockWillBegin
		),
		
		while(currentLevel > previousLevel,
			BlockDelegatesHandling blockWillBegin
			BlockDelegatesHandling blockDidBegin
		)
		while(currentLevel < previousLevel,
			BlockDelegatesHandling blockWillEnd
			BlockDelegatesHandling blockDidEnd
		)
	)
)

Translator putLine := method(
	if(line tokens ?size == 0, return)
	if(currentLevel == 0,
		if(line tokens first isCreator,
			DestinationFile putObjectSignature(line translateObjectSignature),
			DestinationFile putMethodSignature(line translateMethodSignature)
			BlockDelegatesHandling blockDidBegin
		),
		
		putMethodEntryLine(line translateMethodEntryLine)
	)
)

Translator putMethodEntryLine := method(string,
	putCurrentLevels
	DestinationFile write(string .. "\n")
)

Translator insertDeclaration := method(name,
	putMethodEntryLine("Object #{name};" interpolate)
)

Translator translateMainObject := method(
	notBlockingImportObjectType(objectClassName)
	
	DestinationFile write("#include \"internals/basics.h\"\n")
	DestinationFile write("#include \"internals/#{beingProcessedObject}/imports.h\"\n" interpolate)
	DestinationFile write("\n")
	TableOfSymbols pushFrame
	loop(
		line = SourceFile getLine
		if(line isNil, break)
		currentLevel = line getLevel
		putLevel
		putLine
	)
)

Translator notBlockingImportObjectType := method(objectName,
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
	TableOfSymbols imported
)

Translator importObjectType := method(objectName,
	if(TableOfSymbols importing(objectName), return)
	DestinationFile addImport(objectName)
	DestinationFile blockOutput
	notBlockingImportObjectType(objectName)
	DestinationFile unblockOutput
)

BlockDelegatesHandling beforeEachBlockBegins(TableOfSymbols, 5)
BlockDelegatesHandling afterEachBlockBegins(Translator, 5)
System args foreach(index, objectClassName,
	if(index == 0, continue)
	Translator beingProcessedObject = objectClassName
	TableOfSymbols newObjectProcessing
	SourceFile openObjectClass(objectClassName)
	DestinationFile openObjectClass(objectClassName)
	Translator translateMainObject
)
