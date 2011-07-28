Action := Object clone
Action actionName := Token clone

Action comparationMap := Map with(
	"==", "== _equal",
	"<>", "!= _equal",
	"!=", "!= _equal",
	">",  "== _greater",
	"<",  "== _less",
	">=", "!= _less",
	"<=", "!= _greater"
)

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
	toReturn := Actor clone
	
	
	if((actionName beginsWithSeq("Not")) and (actionName != "Not"),
		actionName copy(actionName exclusiveSlice(3))
		toReturn actorName = "Logic_Not(#{actionType actorType}_#{actionName}(#{actor actorName}#{parameters}))" asMutable
		toReturn actorType = "Logic" asMutable,
		
		toReturn actorName = "#{actionType actorType}_#{actionName}(#{actor actorName}#{parameters})" asMutable
		toReturn actorType = "#{actionResult actorType}" asMutable
	)
	
	actionName copy(TableOfSymbols getMainActionNameForActorAndAction(actor, self))
	if(actionName == "=",
		actor2 := line getActor
		if(actor hasProperty("Constant"),
			TranslatorWarning with(line, "Attempt to assign constant object #{actor actorName}." interpolate)
		)
		if(actor hasProperty("Retain"),
			if(actor2 hasProperty("JustCreated") not,
				toReturn actorName = "Object_SetRetaining(&#{actor actorName}, #{actor2 actorName})" asMutable,
				
				toReturn actorName = "Object_SetReleasing(&#{actor actorName}, #{actor2 actorName})" asMutable
			),
			
			if(actor hasProperty("Copy") or actor hasProperty("Clone"),
				if(actor2 hasProperty("JustCreated") not,
					toReturn actorName = "Object_SetCloning(&#{actor actorName}, #{actor2 actorName})" asMutable,
					
					toReturn actorName = "Object_SetReleasing(&#{actor actorName}, #{actor2 actorName})" asMutable
				),
				
				toReturn actorName = "#{actor actorName} = #{actor2 actorName}" asMutable
			)
		)
		if(actor hasProperty("ConstantType"),
			if((actor2 actorType) != (actor actorType),
				TranslatorWarning with(line, "Attempt to change type of constant type object #{actor actorName} from #{actor actorType} to #{actor2 actorType}." interpolate)
			)
		)
		toReturn actorName interpolateInPlace
		toReturn actorType = actor2 actorType
		actor actorType = actor2 actorType
		TableOfSymbols updateActorType(actor)
		return toReturn
	)
	
	if(comparationMap hasKey(actionName),
		toReturn actorName copy("Object_Compare(#{actor actorName}, #{line getActor actorName}) #{comparationMap at(actionName)}" interpolate)
		toReturn actorName copy("LogicFactory_FromLong(_logicFactory, #{toReturn actorName})" interpolate)
		toReturn actorType = "Logic"
		return toReturn
	)
	
	if(actionName beginsWithSeq("As"),
		toReturn actorName copy(actor actorName)
		toReturn actorType copy(actionName exclusiveSlice(2))
		TableOfSymbols ensureKnownClassForClass(toReturn actorType, Translator currentClassName)
		line getParameters
		return toReturn
	)
	
	if(actionName beginsWithSeq("TypeIs"),
		toReturn actorName copy("LogicFactory_FromLong(_logicFactory, #{actor actorName}->gid == #{actionName exclusiveSlice(6) hash asString(20, 0)}ull)" interpolate)
		toReturn actorType = "Logic"
		return toReturn
	)
	
	if(actionName beginsWithSeq("InBackground"),
		toReturn actorName copy("ThreadManager_SpawnThreadWithMethodAndEntity(_threadManager, MethodFactory_FromPointer(_methodFactory, &#{actor actorType}_#{actionName exclusiveSlice(12)}), #{actor actorName})" interpolate)
		toReturn actorType = "ThreadManager"
		return toReturn
	)
	
	if(actionName beginsWithSeq("Dynamically"),
		toReturn actorName copy("Object_DynamicallyInvoke(#{actor actorName}, \"#{actionName exclusiveSlice(11)}\"#{line getParameters})" interpolate)
		toReturn actorType = "Object"
		return toReturn
	)
	
	actionType := getActionType(actor)
	actionResult := actor getReturnedType(self)
	parameters := line getParameters
	
	if(actionName in(list("Clone", "DeepClone")),
		toReturn setProperty("JustCreated")
	)
	
	toReturn actorType interpolateInPlace
	toReturn actorName interpolateInPlace
	TableOfSymbols ensureKnownClassForClass(toReturn actorType, Translator currentClassName)
	toReturn
)
