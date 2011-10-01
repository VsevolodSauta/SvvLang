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

Line getActor := method(
	actor := nil
	if(getCurrentToken beginsNewAction,
		toNextToken
		actor = getActor,
		
		actor = getCurrentToken asActor
		toNextToken
	)
	
	if(getCurrentToken ?endsNewAction,
		toNextToken
		return actor
	)
	toReturn := Action process(actor, self)
	TableOfSymbols ensureKnownClassForClass(toReturn actorType, Translator currentClassName)
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

Line translateGlobalObjectDefinition := method(
	objectName := "_" .. getCurrentToken exclusiveSlice(1)
	objectClass := TableOfSymbols listOfBeingImportedObjects last
	if(objectClass isNil, objectClass = Translator currentClassName)
	TableOfSymbols globalObjects atPut(objectName, objectClass)
	("Object " .. objectName .. ";\n")
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
	
	TableOfSymbols setActorType(Actor fullActor("_self", class, list("Constant")))
	parameters := "Object _self" asMutable
	alternateMethodNames := list()
	name := "" asMutable
	typeOfParameter := "Object"
	propertyList := List clone
	
	while(getCurrentToken isNil not,
		if(getCurrentToken beginsNewAction,
			toNextToken
			while(getCurrentToken endsNewAction not,
				alternateMethodNames append(getCurrentToken)
				toNextToken
			)
			toNextToken
			continue
		)
		if(getCurrentToken looksLikeMethod,
			name appendSeq(getCurrentToken)
			toNextToken
			continue
		)
		if(getCurrentToken isCreator,
			typeOfParameter = getCurrentToken outOfBrackets
			TableOfSymbols ensureKnownClassForClass(typeOfParameter, contextObject)
			toNextToken
			continue
		)
		if(getCurrentToken beginsPropertyList,
			toNextToken
			while(getCurrentToken endsPropertyList not,
				propertyList appendIfAbsent(getCurrentToken)
				toNextToken
			)
			continue
		)
		identifier := "_" .. getCurrentToken
		toNextToken
		TableOfSymbols setActorType(Actor fullActor(identifier, typeOfParameter, propertyList))
		if((Translator isImporting not) and (typeOfParameter != "Object"),
			a := Object clone
			a parameterType := typeOfParameter
			a parameterName := identifier
			a blockDidBegin := method(
				Translator putNLevels(1)
				DestinationFile write("ASSERT_C ( \"#{Translator currentClassName}:#{Translator currentMethodName} --- Checking for correct parameter type failed at parameter #{parameterName}.\", #{parameterName}->gid == #{TableOfSymbols getClassId(parameterType)} || #{parameterName} == _nil )\n" interpolate)
			)
			BlockDelegatesHandling afterThisBlockBegins(a, 4)
		)
		propertyList = List clone
		typeOfParameter = "Object"
		parameters appendSeq(", Object #{identifier}" interpolate)
	)
	
	if(TableOfSymbols listOfBeingImportedObjects isEmpty,
		Translator currentMethodName := name
	)
	TableOfSymbols setClassActionReturnedType(class, Action with(name), Actor unnamedActor(returnType))
	
	alternateMethodNames foreach(altMethodName,
		TableOfSymbols setMainActionNameForActorAndAction(name, Actor unnamedActor(class), Action with(altMethodName))
	)
	
	toPut interpolateInPlace
)

Line translateObjectSignature := method(contextObject, 
	toPut := "typedef struct #{objectName} {\n#{fields}} *#{objectName}"
	objectName := getCurrentToken outOfBrackets split("@") first
	parentName := getCurrentToken outOfBrackets split("@") second
	flagAddToTable := TableOfSymbols classFields at(objectName) empty
	toNextToken
	TableOfSymbols setClassId(objectName, ((objectName hash) mod (Number longMax)) asString(20, 0) .. "ull")
	TableOfSymbols mapOfClassParents atPut(objectName, parentName)
	
	fields := "" asMutable
	if((parentName isNil not) and (parentName != "Object"),
		TableOfSymbols ensureKnownClassForClass(parentName, objectName)
		fields appendSeq("\tstruct #{parentName};\n" interpolate)
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
