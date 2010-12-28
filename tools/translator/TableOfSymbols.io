TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "else", "return", "C", "break", "continue", "loop", "def", "elif", "DEBUG_MSG", "DEBUG_PUSH", "DEBUG_POP")
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release", "Autorelease", "TempClone", "Hash", "Destroy", "Is")
TableOfSymbols basicClasses := list("Object", "Number", "Logic", "Comparation", "Allocator", "NumberFactory", "LogicFactory", "StringFactory", "Console", "Undestroyable")
TableOfSymbols globalObjects := Map with(
	"_nil", "Object", "_nothing", "Object", "_null", "Object",
	"_allocator", "Allocator",
	"_autoreleasePool", "AutoreleasePool",
	"_true", "Logic", "_false", "Logic", "_yes", "Logic", "_no", "Logic",
	"_less", "Comparation", "_greater", "Comparation", "_equal", "Comparation", "_uncomparableLess", "Comparation", "_uncomparableGreater", "Comparation",
	"_numberFactory", "NumberFactory",
	"_logicFactory", "LogicFactory",
//	"_charFactory", "Object",
	"_stringFactory", "StringFactory",
	"_console", "Console"
)

TableOfSymbols tableOfImports := Map clone
TableOfSymbols invalutiveClasses := list("Number", "Logic", "Console")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols globalObjects)
TableOfSymbols classFields := Map clone
TableOfSymbols classMethods := Map with(
	"StringFactory", Map with(
		"FromNumber", Actor unnamedActor("Number")
	)
)
TableOfSymbols listOfBeingImportedObjects := List clone
TableOfSymbols mapOfGids := Map with(
	"Object", "Object" hash asString(20, 0) .. "ull",
	"Number", "Number" hash asString(20, 0) .. "ull"
)

TableOfSymbols mapOfMethodAliases := Map with(
	"Object", Map with(
		"Copy", "Clone",
		"?", "Compare"
	),
	"Number", Map with(
		"+", "Add",
		"-", "Sub",
		"*", "Mul",
		"/", "Div",
		"%", "Mod",
		"+=", "AddInPlace",
		"-=", "SubInPlace",
		"*=", "MulInPlace",
		"/=", "DivInPlace",
		"%=", "ModInPlace",
		"++", "Inc",
		"--", "Dec"
	),
	"Logic", Map with(
		"&", "And",
		"|", "Or",
		"&&", "And",
		"||", "Or",
		"^", "Xor",
		"!", "Not"
	), 
	"Comparation", Map clone,
	"Allocator", Map clone,
	"NumberFactory", Map clone,
	"LogicFactory", Map clone,
	"StringFactory", Map clone,
	"Console", Map clone,
	"Undestroyable", Map clone
)

TableOfSymbols updateActorType := method(actor,
	actorTypesStack foreach(map,
		actorType := map at(actor actorName)
		if(actorType isTrue,
			map atPut(actor actorName, actor actorType)
			return
		)
	)
	currentActorTypesMap atPut(actor actorName, actor actorType)
)

TableOfSymbols setActorType := method(actor,
	currentActorTypesMap atPut(actor actorName, actor actorType)
)

TableOfSymbols getActorType := method(actorName,
	actorTypesStack foreach(map,
		actorType := map at(actorName)
		if(actorType isTrue, return actorType)
	)
	nil
)

TableOfSymbols pushFrame := method(
	currentActorTypesMap = Map clone
	actorTypesStack prepend(currentActorTypesMap)
	self
)

TableOfSymbols popFrame := method(
	actorTypesStack removeFirst
	currentActorTypesMap = actorTypesStack first
	self
)

TableOfSymbols isKeyword := method(token,
	keywords contains(token)
)

TableOfSymbols isObjectsMethod := method(methodName,
	objectsMethods contains(methodName)
)

TableOfSymbols actorHasAction := method(actor, action,
	if(classMethods at(actor actorType) ?at(action actionName) isNil,
		false,
		true
	)
)

TableOfSymbols getActorActionReturnedType := method(actor, action,
	if(isObjectsMethod(action actionName),
		toReturn := Actor unnamedActor(actor actorType),
		
		if(invalutiveClasses contains(actor actorType),
			toReturn := Actor unnamedActor(actor actorType),
			
			toReturn := classMethods at(actor actorType) ?at(action actionName)
			if(toReturn isNil,
				TranslatorError with(nil, "Unknown method #{action actionName} for class #{actor actorType}." interpolate)
				toReturn := Actor unnamedActor("Object")
			)
		)
	)
	toReturn
)

TableOfSymbols setClassActionReturnedType := method(className, action, returnedActor,
	if(classMethods at(className) isNil, classMethods atPut(className, Map clone))
	classMethods at(className) atPut(action actionName, returnedActor)
)

TableOfSymbols setClassField := method(class, actor,
	classFields at(class) append(actor)
	self
)

TableOfSymbols getClassFieldNamed := method(class, fieldName,
	classFieldsList := classFields at(class) 
	if(classFieldsList isNil, TranslatorError with(nil, "Undefined class name #{class}." interpolate))
	classFieldsList foreach(field,
		if(field actorName == fieldName,
			return field
		)
	)
	TranslatorError with(nil, "Unknown class field #{fieldName} in class #{class}." interpolate)
)

TableOfSymbols setClassId := method(class, id,
	mapOfGids atPut(class, id)
)

TableOfSymbols getClassId := method(class,
	mapOfGids at(class)
)

TableOfSymbols import := method(objectType,
	listOfBeingImportedObjects push(objectType)
	pushFrame
)

TableOfSymbols imported := method(
	listOfBeingImportedObjects pop
	popFrame
)

TableOfSymbols importing := method(objectType,
	listOfBeingImportedObjects contains(objectType)
)

TableOfSymbols ensureKnownClassForClass := method(importingType, contextType,
	if(basicClasses contains(importingType), return)
	if(classFields at(importingType) isNil,
		classFields atPut(importingType, List clone)
		mapOfMethodAliases atPut(importingType, Map clone)
		tableOfImports atPut(importingType, List clone)
		Translator importObjectType(importingType)
	)
	if(basicClasses contains(contextType), return)
	if(tableOfImports at(contextType) contains(importingType) not,
		tableOfImports at(contextType) push(importingType)
	)
)

TableOfSymbols newObjectProcessing := method(
	self
)

TableOfSymbols blockWillBegin := method(
	BlockDelegatesHandling afterBlockEnds(TableOfSymbols, 0)
	BlockDelegatesHandling beforeEachBlockBegins(TableOfSymbols, 5)
	pushFrame
)

TableOfSymbols blockDidEnd := method(
	popFrame
)

TableOfSymbols importStringForClass := method(objectType,
	toReturn := "" asMutable
	tableOfImports at(objectType) foreach(importElement,
		toReturn appendSeq("#include \"internals/#{importElement}/interface.h\"\n" interpolate)
	)
	toReturn
)

TableOfSymbols importListForClass := method(objectType,
	tableOfImports at(objectType)
)

TableOfSymbols getMainActionNameForActorAndAction := method(actor, action,
	toReturn := mapOfMethodAliases at("Object") at(action actionName)
	if(toReturn isNil,
		toReturn = mapOfMethodAliases at(actor actorType) at(action actionName)
		if(toReturn isNil,
			action actionName,
			toReturn
		),
		
		toReturn
	)
)

TableOfSymbols setMainActionNameForActorAndAction := method(mainActionName, actor, action,
	mapOfMethodAliases at(actor actorType) atPut(action actionName, mainActionName)
)
