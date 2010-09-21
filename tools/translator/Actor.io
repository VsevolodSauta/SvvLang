Actor := Object clone
Actor actorType := "Object" asMutable clone
Actor actorName := Token clone

Actor clone := method(
	toReturn := Object clone appendProto(Actor)
	toReturn actorType := Actor actorType clone
	toReturn actorName := Actor actorName clone
	toReturn
)

Actor unnamedActor := method(unnamedActorType,
	toReturn := Actor clone
	toReturn actorName copy("[unnamed]")
	toReturn actorType copy(unnamedActorType)
	toReturn
)

Actor with := method(name,
	toReturn := Actor clone
	toReturn actorName copy(name)
	if(toReturn actorName isCreator,
		toReturn actorType = name outOfBrackets
		toReturn actorName copy("#{toReturn actorType}_Create()" interpolate),
	
		toReturn actorType = TableOfSymbols getActorType(name)
		if(toReturn actorType isNil,
			toReturn actorType = "Object"
			TableOfSymbols setActorType(name, "Object")
			Translator insertDeclaration(name)
		)
	)
	toReturn
)

Actor getReturnedType := method(action,
	TableOfSymbols actorActionReturnedType(actorName, action actionName)
)

"Actor read." println
