Line := Object clone
Line string := nil
Line number := nil

Line withStringAndNumber := method(string, number,
	if(string isNil, return nil)
	toReturn := Line clone
	toReturn string = string
	toReturn removeComments
	toReturn number = number
	toReturn
)

Line removeComments := method(
	string = string beforeSeq("//")
)

Line tokens := lazySlot(
	listOfSeparators := list("(", ")", "{", "}", "[", "]")
	toReturn := List clone
	toReturn appendIfNotEmpty := method(string,
		if(string size != 0, self append(string clone))
		string setSize(0)
	)
	parsingString := false
	parsingChar := false
	currentToken := "" asMutable
	escaped := false
	self string foreach(position, charCode,
		char := charCode asCharacter
		if(parsingString,
			currentToken appendSeq(char)
			if(char == "\\",
				if(escaped,
					escaped = false,
					
					escaped = true
				)
				continue
			)
			if(char == "\"",
				if(escaped not,
					toReturn appendIfNotEmpty(currentToken)
					parsingString = false
					continue
				)
			)
			escaped = false
			continue
		)
		if(parsingChar,
			currentToken appendSeq(char)
			if(char == "\\",
				if(escaped,
					escaped = false,
					
					escaped = true
				)
				continue
			)
			if(char == "'",
				if(escaped not,
					toReturn appendIfNotEmpty(currentToken)
					parsingChar = false
					continue
				)
			)
			escaped = false
			continue
		)
		if(char == "\"", 
			toReturn appendIfNotEmpty(currentToken)
			currentToken appendSeq(char)
			parsingString = true
			continue
		)
		if(char == "'",
			toReturn appendIfNotEmpty(currentToken)
			currentToken appendSeq(char)
			parsingChar = true
			continue
		)
		if(listOfSeparators contains(char),
			toReturn appendIfNotEmpty(currentToken)
			toReturn append(char)
			continue
		)
		if((char == " ") or (char == "\t") or (char == "\n") or (char == "\r"),
			toReturn appendIfNotEmpty(currentToken)
			continue
		)
		currentToken appendSeq(char)
	)
	if((parsingChar not) and (parsingString not),
		toReturn appendIfNotEmpty(currentToken),
		TranslatorError with(self, "Line terminated while parsing string or character.")
	)
	toReturn foreach(token, token appendProto(Token))
	toReturn
)

Line getLevel := lazySlot(
	self string foreach(position, charCode,
		if(charCode != 9,
			if(charCode != 32,
				return position,
				
				TranslatorWarning with(self, "Using space for identation. Tab is prefered.")
			)
		)
	)
	0
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
	toReturn := getAction process(actor, self)
	toReturn
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
