#!/usr/local/bin/io

DestinationFile := Object clone

DestinationFile codeFile := File clone
DestinationFile importsFile := File clone
DestinationFile interfacesFile := File clone
DestinationFile cmakeFile := File clone
DestinationFile className := nil

DestinationFile blockingLevel := 0
DestinationFile ignoreBlockingLevelForImport := false

DestinationFile openObjectClass := method(objectClassName,
	Directory directoryNamed("../../internals/#{objectClassName}" interpolate) createIfAbsent
	codeFile = File clone openForUpdating("../../internals/#{objectClassName}/code.c" interpolate)
	importsFile = File clone openForUpdating("../../internals/#{objectClassName}/imports.h" interpolate)
	interfacesFile = File clone openForUpdating("../../internals/#{objectClassName}/interface.h" interpolate)
	cmakeFile = File clone openForUpdating("../../internals/#{objectClassName}/CMakeLists.txt" interpolate)
	blockingLevel = 0
	codeFile truncateToSize(0)
	importsFile truncateToSize(0)
	interfacesFile truncateToSize(0)
	cmakeFile truncateToSize(0)
	className = objectClassName clone
	self
)

DestinationFile with := method(objectClassName,
	DestinationFile clone openObjectClass(objectClassName)
)

DestinationFile write := method(string,
	if(blockingLevel == 0,
		codeFile write(string)
	)
	self
)

DestinationFile putObjectSignature := method(signature,
	if(blockingLevel == 0,
		interfacesFile write(signature .. ";\n\n")
	)
	self
)

DestinationFile putMethodSignature := method(signature,
	if(blockingLevel == 0,
		interfacesFile write(signature .. ";\n")
		self write("\n" .. signature .. "\n")
	)
	self
)

DestinationFile addImport := method(usedObject,
	if((blockingLevel == 0) or (ignoreBlockingLevelForImport),
		writeImport("#include \"internals/#{usedObject}/interface.h\"\n" interpolate)
	)
)

DestinationFile writeImport := method(string,
	importsFile write(string)
)

DestinationFile createCMake := method(listOfImports,
	cmakeFile write(
		list(
			"project(#{className})" interpolate,
			"cmake_minimum_required(VERSION 2.6)",
			"add_library(#{className} ${Library} code.c)" interpolate,
			"target_link_libraries(#{className} #{TableOfSymbols basicClasses join(\" \")} #{listOfImports join(\" \")})" interpolate
		) join("\n")
	)
	self
)

DestinationFile blockOutput := method(
	blockingLevel = blockingLevel + 1
)

DestinationFile unblockOutput := method(
	blockingLevel = blockingLevel - 1
)