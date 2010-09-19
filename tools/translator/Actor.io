Actor := Token clone
Actor actorType := "Object"

Actor with := method(name,
	toReturn := Actor clone
	toReturn copy(name)
	if(toReturn isCreator,
		toReturn actorType = name outOfBrackets
		toReturn copy("#{toReturn actorType}_Create()" interpolate)
		return toReturn
	)
	toReturn actorType = TableOfSymbols getActorType(name)
	if(toReturn actorType isNil,
		TableOfSymbols setActorType(name, "Object")
		Translator insertDeclaration(name)
	)
	toReturn
)

"Actor read." println