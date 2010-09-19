TableOfSymbols := Object clone
TableOfSymbols keywords := list("while", "if", "return")
TableOfSymbols currentActorTypesMap := Map clone
TableOfSymbols actorTypesStack := list(TableOfSymbols currentActorTypesMap)
TableOfSymbols objectsMethods := list("Clone", "Compare", "Retain", "Release")

TableOfSymbols setActorType := method(actor, actorType,
	currentActorTypesMap atPut(actor, actorType)
)

TableOfSymbols getActorType := method(actor,
	actorTypesStack foreach(map,
		actorType := map at(actor)
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