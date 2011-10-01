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
	abstractActor := Actor unnamedActor(actor actorType)
	while(abstractActor actorType isNil not,
		if(TableOfSymbols actorHasAction(abstractActor, self),
			return abstractActor
		)
		abstractActor actorType = TableOfSymbols mapOfClassParents at(abstractActor actorType)
	)
	TranslatorError with(nil, "Method \"#{actionName}\" for object of class \"#{actor actorType}\" not found." interpolate)
)

Action process := method(actor, line,
	localActionName := "" asMutable
	parameters := "" asMutable
	loop(
		if(line getCurrentToken isNil, break)
		if(line getCurrentToken endsNewAction,
			line toNextToken
			break
		)
		
		token := line getCurrentToken
		line toNextToken
		if(token beginsNewAction, 
			parameters appendSeq(", ", line getActor actorName)
			continue
		)
		if(token looksLikeMethod,
			localActionName appendSeq(token)
			if((localActionName == "=") or (comparationMap hasKey(localActionName)), break)
			continue
		)
		
		parameters appendSeq(", ", token asActor actorName)
	)
	if(localActionName == "", return actor)
	
	toReturn := Actor clone
	
	if((localActionName beginsWithSeq("Not")) and (localActionName != "Not"),
		localActionName removeSlice(0, 2)
		toReturn actorName = "Logic_Not(#{actionType actorType}_#{localActionName}(#{actor actorName}#{parameters}))" asMutable
		toReturn actorType = "Logic" asMutable,
		
		toReturn actorName = "#{actionType actorType}_#{localActionName}(#{actor actorName}#{parameters})" asMutable
		toReturn actorType = "#{actionResult actorType}" asMutable
	)
	
	localActionName = TableOfSymbols getMainActionNameForActorAndAction(actor, Action with(localActionName))
	
	if(localActionName == "=",
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
	
	if(comparationMap hasKey(localActionName),
		TableOfSymbols ensureKnownClassForClass("Comparison", Translator objectClassName)
		toReturn actorName copy("Object_Compare(#{actor actorName}, #{line getActor actorName}) #{comparationMap at(localActionName)}" interpolate)
		toReturn actorName copy("LogicFactory_FromLong(_logicFactory, #{toReturn actorName})" interpolate)
		toReturn actorType = "Logic"
		return toReturn
	)
	
	if(localActionName beginsWithSeq("As"),
		toReturn actorName copy(actor actorName)
		toReturn actorType copy(localActionName exclusiveSlice(2))
		return toReturn
	)
	
	if(localActionName beginsWithSeq("TypeIs"),
		toReturn actorName copy("LogicFactory_FromLong(_logicFactory, #{actor actorName}->gid == #{localActionName exclusiveSlice(6) hash asString(20, 0)}ull)" interpolate)
		toReturn actorType = "Logic"
		return toReturn
	)
	
	if(localActionName beginsWithSeq("InBackground"),
		toReturn actorName copy("ThreadManager_SpawnThreadWithMethodAndEntity(_threadManager, MethodFactory_FromPointer(_methodFactory, &#{actor actorType}_#{localActionName exclusiveSlice(12)}), #{actor actorName})" interpolate)
		toReturn actorType = "ThreadManager"
		return toReturn
	)
	
	if(localActionName beginsWithSeq("Dynamically"),
		toReturn actorName copy("Object_DynamicallyInvoke(#{actor actorName}, StringFactory_FromUTF8(_stringFactory, \"#{localActionName exclusiveSlice(11)}\", #{localActionName exclusiveSlice(11) size})#{parameters})" interpolate)
		toReturn actorType = "Object"
		return toReturn
	)
	
	actionType := Action with(localActionName) getActionType(actor)
	actionResult := actor getReturnedType(Action with(localActionName))
	
	if(localActionName in(list("Clone", "DeepClone")),
		toReturn setProperty("JustCreated")
	)
	
	toReturn actorType interpolateInPlace
	toReturn actorName interpolateInPlace
	toReturn
)
