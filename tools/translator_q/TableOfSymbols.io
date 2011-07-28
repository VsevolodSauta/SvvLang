TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "else", "return", "C", "break", "continue", "loop", "def", "elif", "DEBUG_MSG", "DEBUG_PUSH", "DEBUG_POP", "assert")
TableOfSymbols objectsMethods := list("Compare", "Retain", "Release", "Autorelease", "Clone", "TempClone", "DeepClone", "TempDeepClone", "Hash", "Destroy", "Is")
TableOfSymbols basicClasses := list("Object", "Number", "Allocator", "File", "Method", "NumberFactory", "LogicFactory", "StringFactory", "CharFactory", "MethodFactory")
TableOfSymbols globalObjects := Map with(
	"_nil",				"Object",
	"_nothing",			"Object",
	"_null",			"Object",
	"_allocator",			"Allocator",
	"_numberFactory",		"NumberFactory",
	"_logicFactory",		"LogicFactory",
	"_charFactory",			"CharFactory",
	"_stringFactory",		"StringFactory",
	"_methodFactory",		"MethodFactory"
)

TableOfSymbols tableOfImports := Map clone
TableOfSymbols invalutiveClasses := list("Number")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols globalObjects)
TableOfSymbols classFields := Map clone
TableOfSymbols classMethods := Map with(
	"Object", Map with(
		"Compare", Actor unnamedActor("Comparison"),
		"Hash", Actor unnamedActor("Number"),
		"Is", Actor unnamedActor("Logic")
	),
	"Number", Map with(
		"Add", Actor unnamedActor("Number"),
		"Sub", Actor unnamedActor("Number"),
		"Mul", Actor unnamedActor("Number"),
		"Div", Actor unnamedActor("Number"),
		"Mod", Actor unnamedActor("Number"),
		"Inc", Actor unnamedActor("Number"),
		"Dec", Actor unnamedActor("Number"),
		"AddInPlace", Actor unnamedActor("Number"),
		"SubInPlace", Actor unnamedActor("Number"),
		"MulInPlace", Actor unnamedActor("Number"),
		"DivInPlace", Actor unnamedActor("Number"),
		"ModInPlace", Actor unnamedActor("Number"),
		"Min", Actor unnamedActor("Number"),
		"Max", Actor unnamedActor("Number"),
		"Abs", Actor unnamedActor("Number"),
		"Inv", Actor unnamedActor("Number"),
		"Power", Actor unnamedActor("Number"),
		"Set", Actor unnamedActor("Number"),
		"IsInteger", Actor unnamedActor("Logic"),
		"IsOdd", Actor unnamedActor("Logic"),
		"IsEven", Actor unnamedActor("Logic")
	),
	"NumberFactory", Map with(
		"FromLong", Actor unnamedActor("Number"),
		"FromString", Actor unnamedActor("Number"),
		"FromHexString", Actor unnamedActor("Number")
	),
	"StringFactory", Map with(
		"FromNumber", Actor unnamedActor("List")
	),
	"CharFactory", Map with(
		"FromLong", Actor unnamedActor("Char")
	),
	"MethodFactory", Map with(
		"FromPointer", Actor unnamedActor("Method")
	),
	"Method", Map with(
		"Invoke", Actor unnamedActor("Object")
	),
	"File", Map with(
		"OpenForReading", Actor unnamedActor("File"),
		"OpenForAppending", Actor unnamedActor("File"),
		"Close", Actor unnamedActor("File"),
		"TruncateToSize", Actor unnamedActor("File"),
		"SeekToPosition", Actor unnamedActor("File"),
		"Advance", Actor unnamedActor("File"),
		"SeekFromEndToPosition", Actor unnamedActor("File"),
		"GetPosition", Actor unnamedActor("Number"),
		"WriteByte", Actor unnamedActor("File"),
		"WriteNakedString", Actor unnamedActor("File"),
		"WriteNakedNumber", Actor unnamedActor("File"),
		"WriteLnString", Actor unnamedActor("File"),
		"WriteLnNumber", Actor unnamedActor("File"),
		"WriteString", Actor unnamedActor("File"),
		"WriteNumber", Actor unnamedActor("File"),
		"WriteList", Actor unnamedActor("File"),
		"WriteListMap", Actor unnamedActor("File"),
		"ReadByte", Actor unnamedActor("Number"),
		"ReadNumber", Actor unnamedActor("Number"),
		"ReadString", Actor unnamedActor("List"),
		"ReadLnString", Actor unnamedActor("List"),
		"ReadStringOfLength", Actor unnamedActor("List"),
		"ReadChar", Actor unnamedActor("Char"),
		"ReadListMap", Actor unnamedActor("ListMap"),
		"ReadList", Actor unnamedActor("List"),
		"ReadContentsOfFile", Actor unnamedActor("List"),
		"ErrorWhileOpenning", Actor unnamedActor("Logic")
	)
)

TableOfSymbols listOfBeingImportedObjects := List clone
TableOfSymbols mapOfGids := Map with(
	"Object", "Object" hash asString(20, 0) .. "ull",
	"Number", "Number" hash asString(20, 0) .. "ull",
	"File", "File" hash asString(20, 0) .. "ull",
	"Method", "Method" hash asString(20, 0) .. "ull"
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
		"**", "Power",
		"++", "Inc",
		"--", "Dec"
	),
	"Allocator", Map clone,
	"NumberFactory", Map clone,
	"LogicFactory", Map clone,
	"StringFactory", Map clone,
	"File", Map clone,
	"MethodFactory", Map clone,
	"Method", Map with(
		"Call", "Invoke"
	)
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
		if(actorType isTrue, 
			ensureKnownClassForClass(actorType, Translator objectClassName)
			return actorType
		)
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
	toReturn := nil
	if(isObjectsMethod(action actionName),
		candidate := classMethods at("Object") at(action actionName)
		return if(candidate isNil not, candidate, Actor unnamedActor(actor actorType)),
		
		toReturn := classMethods at(actor actorType) ?at(action actionName)
		if(toReturn isNil,
			TranslatorError with(nil, "Unknown method #{action actionName} for class #{actor actorType}." interpolate)
			toReturn = Actor unnamedActor("Object")
		)
		return toReturn
	)
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
	if(basicClasses contains(contextType) not, 
		tableOfImports at(contextType) appendIfAbsent(importingType)
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
