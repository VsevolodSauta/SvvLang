Line := Object clone
Line string := nil

Line withString := method(argument,
	if(argument isNil, return nil)
	toReturn := Line clone
	toReturn string = argument
	toReturn removeComments
	toReturn separateBrackets
	toReturn
)

Line separateBrackets := method(
	string copy(string asMutable replaceSeq("(", "( ") replaceSeq(")", " )"))
)

Line removeComments := method(
	string = string beforeSeq("//")
)

tokens := lazySlot(
	toReturn := self string ?splitNoEmpties
	toReturn foreach(token, token appendProto(Token))
	toReturn
)

tokenz := lazySlot(
	self string ?split
)

Line getLevel := lazySlot(
	broken := false
	level := 0
	tokenz ?foreach(token,
		if(token == "",
			level = level + 1,
			broken = true
			break
		)
	)
	if(broken,
		level,
		0
	)
)

Line translateMethodSignature := method(
	TableOfSymbols popFrame pushFrame
	toPut := "Object #{class}_#{name}(#{parameters})"
	class := tokens at(0)
	name := tokens at(1)
	parameters := "Object self" asMutable
	TableOfSymbols setActorType("self", class)
	typeOfParameter := "Object"
	tokens foreach(index, token, 
		if(index < 2, continue)
		if(token isCreator,
			typeOfParameter = token outOfBrackets
			continue
		)
		TableOfSymbols setActorType(token, typeOfParameter)
		typeOfParameter = "Object"
		parameters appendSeq(", Object #{token}" asMutable interpolateInPlace)
	)
	DestinationFile write(toPut interpolate)
)

Line currentTokenNumber := 0

Line toNextToken := method(
	currentTokenNumber = (currentTokenNumber + 1)
)

Line getCurrentToken := method(
	tokens at(currentTokenNumber)
)

Line getParameters := method(
	toReturn := "" asMutable
	while(currentTokenNumber < (tokens size),
		token := getCurrentToken
		if(token endsNewAction, 
			toNextToken
			return toReturn
		)
		if(token beginsNewAction, 
			toNextToken
			toReturn appendSeq(", ") appendSeq(getActor actorName)
			continue
		)
		toReturn appendSeq(", ") appendSeq(token)
		toNextToken
	)
	toReturn
)

Line getAction := method(
	toReturn := getCurrentToken asAction
	toNextToken
	toReturn
)

Line getActor := method(
	toReturn := Actor clone
	toReturn actorName = "#{actionType actorType}_#{action actionName}(#{actor actorName}#{parameters})" asMutable
	toReturn actorType = "Object"
	
	if(getCurrentToken beginsNewAction,
		toNextToken
		actor := getActor,
		
		actor := getCurrentToken asActor
		toNextToken
	)
	actor actorName println
	
	if(getCurrentToken isNil,
		return actor
	)
	
	if(getCurrentToken endsNewAction,
		toNextToken
		return actor
	)
	
	action := getAction
	action actionName println
	if(action actionName == "=",
		actor2 := getActor
		toReturn actorName = "#{actor actorName} = #{actor2 actorName}" asMutable interpolateInPlace
		TableOfSymbols setActorType(actor actorName, actor2 actorType)
		toReturn actorType = actor2 actorType,
	
		actionType := action getActionType(actor)
		actionResult := actionType getReturnedType(action)
		parameters := getParameters
		// toReturn actorName interpolateInPlace
		toReturn actorType = actionResult actorType
	)
	toReturn actorName interpolateInPlace
	toReturn
)

Line translateMethodEntryLine := method(
	first := getCurrentToken
	if(first isKeyword,
		first processKeyword(self),
		DestinationFile write((getActor actorName) .. ";")
	)
)
