Action := Object clone
Action actionName := Token clone

Action clone := method(
	toReturn := Object clone appendProto(Action)
	toReturn actionName := Action actionName clone
	toReturn
)

Action with := method(token,
	toReturn := Action clone
	toReturn actionName copy(token)
	toReturn
)

Action getActionType := method(actor,
	if(TableOfSymbols isObjectsMethod(actionName),
		return Actor unnamedActor("Object"),
		return Actor unnamedActor(actor actorType)
	)
)

