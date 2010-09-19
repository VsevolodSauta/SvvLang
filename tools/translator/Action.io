Action := Object clone

Action getActionType := method(actor,
	if(TableOfSymbols isObjectsMethod(self),
		return "Object",
		TableOfSymbols getActorType(actor)
	)
)
