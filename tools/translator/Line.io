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

Line tokens := lazySlot(
	toReturn := self string ?splitNoEmpties
	toReturn foreach(token, token appendProto(Token))
	toReturn
)

Line tokenz := lazySlot(
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
		toReturn appendSeq(", ") appendSeq(token asActor actorName)
		toNextToken
	)
	toReturn
)

Line getAction := method(
	toReturn := getCurrentToken asAction
	toNextToken
	toReturn
)

Line getActor := method(isComparation,
	if(getCurrentToken beginsNewAction,
		toNextToken
		actor := getActor,
		
		actor := getCurrentToken asActor
		toNextToken
	)
	
	if(getCurrentToken isNil,
		return actor
	)
	
	if(getCurrentToken endsNewAction,
		toNextToken
		return actor
	)
	
	getAction process(actor, self, isComparation)
)

Line getCondition := method(
	actor := getActor(true)
	if(actor actorType != "[int],
		Exception raise("""Actor #{actor actorName} has #{actor actorType} type, but [int] expected.""" interpolate)
	)
	
	actor actorName
)

Line translateMethodEntryLine := method(
	first := getCurrentToken
	if(first isKeyword,
		first asKeyword process(self),
		DestinationFile write((getActor(false) actorName) .. ";")
	)
)

Line translateMethodSignature := method(
	TableOfSymbols pushFrame
	toPut := "Object #{class}_#{name}(#{parameters})"
	class := tokens at(0)
	second := tokens at(1)
	if(second isCreator,
		returnType := second outOfBrackets
		TableOfSymbols ensureKnownClass(returnType)
		name := tokens at(2)
		parametersBeginAt := 3,
		
		name := second
		returnType := class
		parametersBeginAt := 2
	)
	TableOfSymbols setClassActionReturnedType(class, Action with(name), Actor unnamedActor(returnType))
	parameters := "Object self" asMutable
	TableOfSymbols setActorType(Actor fullActor("self", class))
	typeOfParameter := "Object"
	tokens foreach(index, token, 
		if(index < parametersBeginAt, continue)
		if(token isCreator,
			typeOfParameter = token outOfBrackets
			TableOfSymbols ensureKnownClass(typeOfParameter)
			continue
		)
		TableOfSymbols setActorType(Actor fullActor(token, typeOfParameter))
		typeOfParameter = "Object"
		parameters appendSeq(", Object #{token}" asMutable interpolateInPlace)
	)
	DestinationFile write(toPut interpolate)
)

Line translateObjectSignature := method(
	toPut := "typedef struct #{objectName} {\n#{fields}} *#{objectName};\n"
	objectName := tokens at(0) outOfBrackets
	if(objectName != (Translator beingProcessedObject), toPut = "")
	
	fields := "" asMutable
	typeOfParameter := "Object"
	tokens foreach(index, token, 
		if(index < 1, continue)
		if(token isCreator,
			typeOfParameter = token outOfBrackets
			TableOfSymbols ensureKnownClass(typeOfParameter)
			continue
		)
		TableOfSymbols setFieldType(objectName, token, typeOfParameter)
		typeOfParameter = "Object"
		fields appendSeq("\tObject #{token};\n" asMutable interpolateInPlace)
	)
	DestinationFile write(toPut interpolate)
)
