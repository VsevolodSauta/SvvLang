TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "return")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols currentActorTypesMap)
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release", "Autorelease", "TempClone")
TableOfSymbols classFields := Map clone

TableOfSymbols updateActorType := method(actorName, actorType,
	actorTypesStack foreach(map,
		actorType := map at(actorName)
		if(actorType isTrue,
			map atPut(actorName, actorType)
			return
		)
	)
	currentActorTypesMap atPut(actorName, actorType)
)

TableOfSymbols setActorType := method(actorName, actorType,
	currentActorTypesMap atPut(actorName, actorType)
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
	Actor unnamedActor("Object")
)

TableOfSymbols setFieldType := method(class, field, fieldType,
	if(classFields at(class) isNil, classFields atPut(class, Map clone))
	classFields at(class) atPut(field, fieldType)
	self
)

TableOfSymbols getFieldType := method(class, field,
	classField at(class) at(field)
)
