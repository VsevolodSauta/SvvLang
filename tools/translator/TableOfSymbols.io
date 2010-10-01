TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "else", "return", "C", "break", "continue", "loop", "def", "elif")
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release", "Autorelease", "TempClone", "Hash")
TableOfSymbols basicClasses := list("Object", "Number", "Logic", "Comparation", "Allocator", "NumberFactory", "LogicFactory")
TableOfSymbols globalObjects := Map with(
	"_nil", "Object", "_nothing", "Object",
	"_allocator", "Allocator",
	"_autoreleasePool", "AutoreleasePool",
	"_true", "Logic", "_false", "Logic", "_yes", "Logic", "_no", "Logic",
	"_less", "Comparation", "_greater", "Comparation", "_equal", "Comparation", "_uncomparableLess", "Comparation", "_uncomparableGreater",
	"_numberFactory", "NumberFactory",
	"_logicFactory", "LogicFactory",
	"_charFactory", "Object",
	"_stringFactory", "Object"
)

TableOfSymbols tableOfImports := Map clone
TableOfSymbols invalutiveClasses := list("Number", "Logic")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols globalObjects)
TableOfSymbols classFields := Map clone
TableOfSymbols classMethods := Map clone
TableOfSymbols listOfBeingImportedObjects := List clone
TableOfSymbols mapOfGids := Map with(
	"Object", "Object" hash,
	"Number", "Number" hash
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
	"LogicFactory", Map clone
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
			if(toReturn isNil, toReturn := Actor unnamedActor("Object"))
		)
	)
	toReturn
)

TableOfSymbols setClassActionReturnedType := method(className, action, returnedActor,
	if(classMethods at(className) isNil, classMethods atPut(className, Map clone))
	classMethods at(className) atPut(action actionName, returnedActor)
)

TableOfSymbols setFieldType := method(class, field, fieldType,
	classFields at(class) atPut(field, fieldType)
	self
)

TableOfSymbols getFieldType := method(class, field,
	classMap := classFields at(class) 
	if(classMap isNil, Exception raise("Undefined class name #{class}." interpolate))
	fieldType := classMap at(field)
	if(fieldType isNil, Exception raise("Unknown class field #{field} in class #{class}." interpolate))
	fieldType
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
		classFields atPut(importingType, Map clone)
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
	toReturn := mapOfMethodAliases at(actor actorType) at(action actionName)
	if(toReturn isNil,
		toReturn = mapOfMethodAliases at("Object") at(action actionName)
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