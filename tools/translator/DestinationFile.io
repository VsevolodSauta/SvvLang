#!/usr/local/bin/io

DestinationFile := Object clone

DestinationFile codeFile := File clone
DestinationFile importsFile := File clone
DestinationFile interfacesFile := File clone

DestinationFile blockingLevel := 0
DestinationFile ignoreBlockingLevelForImport := false

DestinationFile openObjectClass := method(objectClassName,
	Directory directoryNamed("../../internals/#{objectClassName}" interpolate) createIfAbsent
	codeFile = File clone openForUpdating("../../internals/#{objectClassName}/code.c" interpolate)
	importsFile = File clone openForUpdating("../../internals/#{objectClassName}/imports.h" interpolate)
	interfacesFile = File clone openForUpdating("../../internals/#{objectClassName}/interface.h" interpolate)
	blockingLevel = 0
	codeFile truncateToSize(0)
	importsFile truncateToSize(0)
	interfacesFile truncateToSize(0)
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
		importsFile write("#include \"internals/#{usedObject}/interface.h\"\n" interpolate)
	)
)

DestinationFile blockOutput := method(
	blockingLevel = blockingLevel + 1
)

DestinationFile unblockOutput := method(
	blockingLevel = blockingLevel - 1
)