#!/usr/local/bin/io

Translator := Object clone
Translator previousLevel := 0
Translator currentLevel := 0
Translator line := nil
Translator isImporting := method(
	TableOfSymbols listOfBeingImportedObjects isEmpty not
)

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

Translator translateLevel := method(
	if(Translator line ?tokens ?size == 0, return)
	if((currentLevel == 0),
		while(currentLevel < previousLevel,
			BlockDelegatesHandling blockWillEnd
			BlockDelegatesHandling blockDidEnd
		)
		if(line tokens first looksLikeMethodDefinition,
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

Translator putMethodEntryLine := method(string,
	putCurrentLevels
	DestinationFile write(string .. "\n")
)

Translator insertDeclaration := method(name,
	putMethodEntryLine("Object #{name};" interpolate)
)

Translator translateClass := method(objectClassName,
	SourceFile = SourceFile with(objectClassName)
	DestinationFile openObjectClass(objectClassName)
	Translator currentClassName := objectClassName
	
	DestinationFile write("#include \"internals/basics.h\"\n")
	DestinationFile write("#include \"internals/#{objectClassName}/imports.h\"\n" interpolate)
	DestinationFile write("\n")
	
	TableOfSymbols ensureKnownClassForClass("Logic", objectClassName)
	TableOfSymbols ensureKnownClassForClass("SuperClass", objectClassName)
	
	TableOfSymbols pushFrame
	loop(
		line = SourceFile getLine
		if(line isNil, break)
		currentLevel = line getLevel
		if(line tokens ?size == 0, continue)
		translateLevel
		if(currentLevel == 0,
			if(line tokens first isCreator,
				DestinationFile putObjectSignature(line translateObjectSignature(objectClassName))
				actor := Actor unnamedActor(line tokens first outOfBrackets)
				DestinationFile putMethodSignature(actor getCreatorSignature)
				DestinationFile write(actor getCreatorBody)
				continue
			)
			if(line tokens first isGlobalObjectDefinition,
				DestinationFile putGlobalObjectDefinition(line translateGlobalObjectDefinition)
				continue
			)
			
			DestinationFile putMethodSignature(line translateMethodSignature(objectClassName))
			BlockDelegatesHandling blockDidBegin,
			
			putMethodEntryLine(line translateMethodEntryLine(objectClassName))
		)
	)
	while(0 < previousLevel,
		BlockDelegatesHandling blockWillEnd
		BlockDelegatesHandling blockDidEnd
	)
	
	DestinationFile write("void #{objectClassName}_IntializeClass()\n" interpolate)
	DestinationFile write("{\n")
	//DestinationFile write("\tAutoreleasePool_PushFrame(_autoreleasePool);\n");
	DestinationFile write("\tObject _className = StringFactory_FromUTF8(_stringFactory, \"#{objectClassName}\", #{objectClassName size});\n" interpolate)
	TableOfSymbols classMethods at(objectClassName) foreach(methodName, methodResultClass,
		DestinationFile write("\tSuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &#{objectClassName}_#{methodName}), StringFactory_FromUTF8(_stringFactory, \"#{methodName}\", #{methodName size}), _className);\n" interpolate)
	)
	TableOfSymbols mapOfMethodAliases at(objectClassName) foreach(methodName, realMethodName,
		DestinationFile write("\tSuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &#{objectClassName}_#{realMethodName}), StringFactory_FromUTF8(_stringFactory, \"#{methodName asMutable escape}\", #{methodName size}), _className);\n" interpolate)
	)
	//DestinationFile write("\tAutoreleasePool_PopFrame(_autoreleasePool);\n");
	DestinationFile write("}")
)

Translator importAll := method(
	Translator currentClassName := "Object"
	Directory with("../../internals_sources_q") files foreach(file,
		if(file name endsWithSeq(".q"),
			TableOfSymbols ensureKnownClassForClass(file name exclusiveSlice(0, file name size - 2), "Object")
		)
	)
)

Translator importObjectType := method(objectClassNameToImport,
	TableOfSymbols import(objectClassNameToImport)
	fileToImport := SourceFile with(objectClassNameToImport)
	loop(
		line := fileToImport getLine
		if(line isNil, break)
		currentLevel := line getLevel
		if(line tokens ?size == 0, continue)
		if(currentLevel != 0, continue)
		if(line tokens first isCreator,
			line translateObjectSignature(objectClassNameToImport)
			continue
		)
		if(line tokens first isGlobalObjectDefinition,
			line translateGlobalObjectDefinition
			continue
		)
		line translateMethodSignature(objectClassNameToImport)
	)
	TableOfSymbols imported
)

BlockDelegatesHandling beforeEachBlockBegins(TableOfSymbols, 5)
BlockDelegatesHandling afterEachBlockBegins(Translator, 5)
BlockDelegatesHandling afterEachBlockBegins(TranslatorDebugger, 4)

Translator importAll

if(System args size == 1,
	toProcessList := List clone
	Directory with("../../internals_sources_q") files foreach(file,
		if(file name endsWithSeq(".q"),
			toProcessList push(file baseName)
		)
	),
	
	toProcessList := System args slice(1)
)

toProcessList foreach(index, objectClassName,
	"=============== #{objectClassName alignCenter(30)} ===============" interpolate println
	Translator currentClassName := objectClassName
	TableOfSymbols ensureKnownClassForClass(objectClassName, "Object")
	TableOfSymbols newObjectProcessing
	Translator translateClass(objectClassName)
	DestinationFile writeImport(TableOfSymbols importStringForClass(objectClassName))
	DestinationFile createCMake(TableOfSymbols importListForClass(objectClassName) remove(objectClassName))
)

FinalStage perform