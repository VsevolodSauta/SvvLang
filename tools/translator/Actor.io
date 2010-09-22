Actor := Object clone
Actor actorType := "Object" asMutable clone
Actor actorName := Token clone

Actor clone := method(
	toReturn := Object super(clone)
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

Actor fullActor := method(fullActorName, fullActorType,
	toReturn := Actor clone
	toReturn actorName copy(fullActorName)
	toReturn actorType copy(fullActorType)
	toReturn
)

Actor with := method(name,
	toReturn := Actor clone
	
	if(name isCreator,
		toReturn actorType = name outOfBrackets
		toReturn actorName copy("#{toReturn actorType}_Create()" interpolate),
	
		listOfFields := name split(".")
		listOfFields foreach(index, field,
			if(index == 0,
				toReturn actorName copy(field)
				toReturn actorType = TableOfSymbols getActorType(field)
				if(toReturn actorType isNil,
					if(listOfFields size != 1, Exception raise("No fields in object Object found."))
					toReturn actorType = "Object"
					TableOfSymbols setActorType(toReturn)
					Translator insertDeclaration(field)
				),
				
				toReturn actorName prependSeq("ENTITY(") appendSeq(", #{toReturn actorType})->#{field}" interpolate)
				toReturn actorType = TableOfSymbols getFieldType(toReturn actorType, field)
			)
		)
	)
	toReturn
)

Actor getReturnedType := method(action,
	TableOfSymbols actorActionReturnedType(self, action)
)

