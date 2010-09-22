TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "return", "C")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := List clone
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release", "Autorelease", "TempClone")
TableOfSymbols classFields := Map clone
TableOfSymbols classMethods := Map clone
TableOfSymbols listOfBeingImportedObjects := List clone
TableOfSymbols basicClasses := list("[int]", "Object", "Number")

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

TableOfSymbols getActorActionReturnedType := method(actor, action,
	if(isObjectsMethod(action actionName),
		toReturn := Actor unnamedActor(actor actorType),
		
		toReturn := classMethods at(actor actorType) ?at(action actionName)
		if(toReturn isNil, toReturn := Actor unnamedActor("Object"))
	)
	toReturn
)

TableOfSymbols setClassActionReturnedType := method(className, action, returnedActor,
	if(classMethods at(className) isNil, classMethods atPut(className, Map clone))
	classMethods at(className) atPut(action actionName, returnedActor)
)

TableOfSymbols setFieldType := method(class, field, fieldType,
	if(classFields at(class) isNil, classFields atPut(class, Map clone))
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

TableOfSymbols import := method(objectType,
	listOfBeingImportedObjects push(objectType)
)

TableOfSymbols imported := method(
	listOfBeingImportedObjects pop
)

TableOfSymbols importing := method(objectType,
	listOfBeingImportedObjects contains(objectType)
)

TableOfSymbols ensureKnownClass := method(objectType,
	if(basicClasses contains(objectType), return)
	if(classFields at(objectType) isNil,
		Translator importObjectType(objectType)
	)
)