Line := Object clone
Line string := nil
Line number := nil

Line preprocessingMap := Map with(
	"(", "( ",
	")", " )",
	"[", "[ ",
	"]", " ]",
	"{", "{ ",
	"}", " }"
)

Line withStringAndNumber := method(string, number,
	if(string isNil, return nil)
	toReturn := Line clone
	toReturn string = string
	toReturn removeComments
	toReturn separateBrackets
	toReturn number = number
	toReturn
)

Line separateBrackets := method(
	stringToProcess := string asMutable
	preprocessingMap foreach(leftSide, rightSide,
		stringToProcess replaceSeq(leftSide, rightSide)
	)
	string copy(stringToProcess)
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

Line readString := method(
	toReturn := "" asMutable appendProto(Token)
	while(getCurrentToken beginsString,
		toReturn appendSeq(getCurrentToken exclusiveSlice(1))
		toNextToken
		while(toReturn endsString not,
			toReturn appendSeq(" ", getCurrentToken)
			toNextToken
		)
		toReturn removeLast
		if(getCurrentToken isNil, break)
	)
	"\"#{toReturn}\"" interpolate appendProto(Token)
)

Line getActor := method(
	if(getCurrentToken beginsNewAction,
		toNextToken
		actor := getActor,
			
		if(getCurrentToken beginsString,
			actor := readString asActor,
			
			actor := getCurrentToken asActor
			toNextToken
		)
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
	TableOfSymbols setActorType(Actor fullActor("_self", class, list("Constant")))
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
		propertyList := List clone
		while(getCurrentToken isNil not,
			token := getCurrentToken
			toNextToken
			if(token isCreator,
				typeOfParameter = token outOfBrackets
				TableOfSymbols ensureKnownClassForClass(typeOfParameter, contextObject)
				continue
			)
			if(token beginsPropertyList,
				toNextToken
				while(getCurrentToken endsPropertyList not,
					propertyList appendIfAbsent(getCurrentToken)
					toNextToken
				)
			)
			token = "_" .. token
			TableOfSymbols setActorType(Actor fullActor(token, typeOfParameter, propertyList))
			propertyList = List clone
			typeOfParameter = "Object"
			parameters appendSeq(", Object #{token}" asMutable interpolateInPlace)
		)
	)
	toPut interpolateInPlace
)

Line translateObjectSignature := method(contextObject, 
	toPut := "typedef struct #{objectName} {\n#{fields}} *#{objectName}"
	objectName := getCurrentToken outOfBrackets
	flagAddToTable := TableOfSymbols classFields at(objectName) empty
	toNextToken
	TableOfSymbols setClassId(objectName, ((objectName hash) mod (Number longMax)) asString(20, 0) .. "ull")
	
	fields := "" asMutable
	typeOfParameter := "Object"
	propertyList := List clone
	while(getCurrentToken isNil not,
		token := getCurrentToken
		toNextToken
		if(token isCreator,
			typeOfParameter = token outOfBrackets
			TableOfSymbols ensureKnownClassForClass(typeOfParameter, contextObject)
			continue
		)
		if(token beginsPropertyList,
			while(getCurrentToken endsPropertyList not,
				propertyList appendIfAbsent(getCurrentToken)
				toNextToken
			)
			toNextToken
			continue
		)
		token = "_" .. token
		if(flagAddToTable,
			TableOfSymbols setClassField(objectName, Actor fullActor(token, typeOfParameter, propertyList))
		)
		propertyList = List clone
		typeOfParameter = "Object"
		fields appendSeq("\tObject #{token};\n" interpolate)
	)
	toPut interpolate
)
