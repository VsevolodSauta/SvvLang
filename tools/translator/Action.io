Action := Object clone
Action actionName := Token clone
Action comparationOperationsList := list("==", "<>", "!=", ">", "<", "<=", ">=")
Action comparationTypeMap := Map with(
	"==", "==", 
	"<>", "!=", 
	"!=", "!=",
	">", "==",
	"<", "==",
	">=", "!=",
	"<=", "!="
)

Action comparationValueMap := Map with(
	"==", "_equal", 
	"<>", "_equal", 
	"!=", "_equal",
	">", "_greater",
	"<", "_less",
	">=", "_less",
	"<=", "_greater"
)


Action clone := method(
	toReturn := Object super(clone)
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

Action process := method(actor, line,
	actionName copy(TableOfSymbols getMainActionNameForActorAndAction(actor, self))
	toReturn := Actor clone
	if(actionName == "=",
		actor2 := line getActor
		toReturn actorName = "#{actor actorName} = #{actor2 actorName}" asMutable interpolateInPlace
		toReturn actorType = actor2 actorType
		actor actorType = actor2 actorType
		TableOfSymbols updateActorType(actor)
		return toReturn
	)
	
	if(comparationOperationsList contains(actionName),
		toReturn actorName copy("Object_Compare(#{actor actorName}, #{line getActor actorName}) #{comparationTypeMap at(actionName)} #{comparationValueMap at(actionName)}" interpolate)
		toReturn actorName copy("LogicFactory_FromLong(_logicFactory, #{toReturn actorName})" interpolate)
		toReturn actorType = "Logic"
		return toReturn
	)
	
	if(actionName beginsWithSeq("As"),
		toReturn actorName copy(actor actorName)
		toReturn actorType copy(actionName exclusiveSlice(2))
		line getParameters
		return toReturn
	)
	
	if(actionName beginsWithSeq("Not"),
		actionName copy(actionName exclusiveSlice(3))
		toReturn actorName = "Logic_Not(#{actionType actorType}_#{actionName}(#{actor actorName}#{parameters}))" asMutable
		toReturn actorType = "Logic" asMutable,
		
		toReturn actorName = "#{actionType actorType}_#{actionName}(#{actor actorName}#{parameters})" asMutable
		toReturn actorType = "#{actionResult actorType}" asMutable
	)
	
	actionType := getActionType(actor)
	actionResult := actor getReturnedType(self)
	parameters := line getParameters
	
	toReturn actorType interpolateInPlace
	toReturn actorName interpolateInPlace
	toReturn
)
