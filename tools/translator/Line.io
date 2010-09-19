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
			toReturn appendSeq(", ") appendSeq(getAction)
			continue
		)
		toReturn appendSeq(", ") appendSeq(token)
		toNextToken
	)
	toReturn
)

Line getAction := method(
	toReturn := "#{actionType}_#{action}(#{actor}#{parameters})"
	actor := getCurrentToken asActor
	toNextToken
	action := getCurrentToken ?asAction
	if(action isNil, return actor)
	if(action endsNewAction, 
		toNextToken
		return actor
	)
	parameters := ""
	action switch(
		"=",
			toNextToken
			toReturn = "#{actor} = #{getAction}",
		
		toNextToken
		actionType := action getActionType(actor)
		parameters := getParameters
	)
	toReturn interpolate
)

Line translateMethodEntryLine := method(
	first := getCurrentToken
	if(first isKeyword,
		first processKeyword(self),
		DestinationFile write(getAction .. ";")
	)
)
