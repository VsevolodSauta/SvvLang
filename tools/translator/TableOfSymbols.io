TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "return")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols currentActorTypesMap)
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release", "Autorelease", "TempClone")
TableOfSymbols classFields := Map clone

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
	currentActorTypesMap := Map clone
	actorTypesStack prepend(currentActorTypesMap)
	self
)

TableOfSymbols popFrame := method(
	actorTypesStack removeFirst
	self
)

TableOfSymbols isKeyword := method(token,
	keywords contains(token)
)

TableOfSymbols isObjectsMethod := method(methodName,
	objectsMethods contains(methodName)
)

TableOfSymbols actorActionReturnedType := method(actor, action,
	if(isObjectsMethod(action actionName),
		toReturn := Actor unnamedActor(actor actorType),
		
		toReturn := Actor unnamedActor("Object")
	)
	"Type of action #{action actionName} on #{actor actorName} of #{actor actorType} type: " interpolate print
	toReturn actorType println
	toReturn
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
