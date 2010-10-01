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

Line getActor := method(
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
	
	getAction process(actor, self)
)

Line getCondition := method(
	"(#{getActor actorName}) != _false" interpolate
)

Line translateMethodEntryLine := method(
	first := getCurrentToken
	if(first isKeyword,
		return first asKeyword process(self),
		return getActor actorName .. ";"
	)
)

Line translateMethodSignature := method(contextObject, 
	toPut := "Object #{class}_#{name}(#{parameters})" asMutable
	class := getCurrentToken
	returnType := class
	toNextToken
	while(getCurrentToken isCreator,
		returnType = getCurrentToken outOfBrackets
		TableOfSymbols ensureKnownClassForClass(returnType, contextObject)
		toNextToken
	)
	name := getCurrentToken
	toNextToken
	TableOfSymbols setClassActionReturnedType(class, Action with(name), Actor unnamedActor(returnType))
	
	parameters := "Object _self" asMutable
	TableOfSymbols setActorType(Actor fullActor("_self", class))
	if(getCurrentToken isNil not,
		if(getCurrentToken beginsNewAction,
			loop(
				toNextToken
				
				if(getCurrentToken endsNewAction,
					toNextToken
					break
				)
				
				TableOfSymbols setMainActionNameForActorAndAction(name, Actor unnamedActor(class), Action with(getCurrentToken))
			)
		)
		
		typeOfParameter := "Object"
		while(getCurrentToken isNil not,
			token := getCurrentToken
			toNextToken
			if(token isCreator,
				typeOfParameter = token outOfBrackets
				TableOfSymbols ensureKnownClassForClass(typeOfParameter, contextObject)
				continue
			)
			token = "_" .. token
			TableOfSymbols setActorType(Actor fullActor(token, typeOfParameter))
			typeOfParameter = "Object"
			parameters appendSeq(", Object #{token}" asMutable interpolateInPlace)
		)
	)
	toPut interpolateInPlace
)

Line translateObjectSignature := method(contextObject, 
	toPut := "typedef struct #{objectName} {\n#{fields}} *#{objectName}"
	objectName := tokens at(0) outOfBrackets
	TableOfSymbols setClassId(objectName, ((objectName hash) mod (Number longMax)) asString(20, 0) .. "ull")
	
	fields := "" asMutable
	typeOfParameter := "Object"
	tokens foreach(index, token, 
		if(index < 1, continue)
		if(token isCreator,
			typeOfParameter = token outOfBrackets
			TableOfSymbols ensureKnownClassForClass(typeOfParameter, contextObject)
			continue
		)
		token = "_" .. token
		TableOfSymbols setFieldType(objectName, token, typeOfParameter)
		typeOfParameter = "Object"
		fields appendSeq("\tObject #{token};\n" interpolate)
	)
	toPut interpolate
)
