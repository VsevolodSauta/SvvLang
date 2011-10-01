Actor := Object clone
Actor actorType := "Object" asMutable clone
Actor actorName := Token clone
Actor properties := List clone

Actor clone := method(
	toReturn := Object super(clone)
	toReturn actorType := Actor actorType clone
	toReturn actorName := Actor actorName clone
	toReturn properties := Actor properties clone
	toReturn
)

Actor unnamedActor := method(unnamedActorType, 
	toReturn := Actor clone
	toReturn actorName copy("[unnamed]")
	toReturn actorType copy(unnamedActorType)
	toReturn properties = list("Constant")
	toReturn
)

Actor fullActor := method(fullActorName, fullActorType, fullActorProperties,
	toReturn := Actor clone
	toReturn actorName copy(fullActorName)
	toReturn actorType copy(fullActorType)
	toReturn properties = fullActorProperties
	toReturn
)

Actor with := method(name,
	name stringUnescapedSize := method(
		toReturn := 0
		escaped := false
		foreach(code, 
			char := code asCharacter
			if(escaped,
				escaped = false
				toReturn = toReturn + 1
				continue
			)
			if(char == "\\", 
				escaped = true,
				toReturn = toReturn + 1
			)
		)
		toReturn - 2
	)
	
	toReturn := Actor clone
	
	if(name isCreator,
		toReturn actorType = name outOfBrackets
		TableOfSymbols ensureKnownClassForClass(toReturn actorType, Translator currentClassName)
		toReturn actorName copy("#{toReturn actorType}_Create()" interpolate)
		toReturn setProperty("JustCreated")
		return toReturn
	)
	
	if(name isNumber,
		toReturn actorType = "Number"
		toReturn actorName copy("NumberFactory_FromLong(_numberFactory, #{name})" interpolate)
		return toReturn
	)
	
	if(name isString,
		toReturn actorType = "List"
		toReturn actorName copy("StringFactory_FromUTF8(_stringFactory, \"#{name outOfBrackets asMutable}\", #{name stringUnescapedSize})" interpolate)
		return toReturn
	)
	
	if(name isChar,
		toReturn actorType = "Char"
		toReturn actorName copy("CharFactory_FromLong(_charFactory, #{name})" interpolate)
		return toReturn
	)
	
	if(name isPointer,
		toReturn actorType = "Method"
		toReturn actorName copy("MethodFactory_FromPointer(_methodFactory, #{name})" interpolate)
		return toReturn
	)
	
	listOfFieldNames := name split(".")
	listOfFieldNames foreach(index, fieldName,
		fieldName = "_" .. fieldName
		if(index == 0,
			if(fieldName == "_super",
				toReturn actorName copy("_self")
				toReturn actorType = TableOfSymbols mapOfClassParents at(TableOfSymbols getActorType("_self")),
				
				toReturn actorName copy(fieldName)
				toReturn actorType = TableOfSymbols getActorType(fieldName)
			)
			
			if(toReturn actorType isNil,
				if(listOfFieldNames size != 1,
					TranslatorError with(nil, "No fields in object #{fieldName} of Object type found." interpolate)
				)
				toReturn actorType = "Object"
				TableOfSymbols setActorType(toReturn)
				Translator insertDeclaration(fieldName)
			),
			
			actor := TableOfSymbols getClassFieldNamed(toReturn actorType, fieldName)
			toReturn actorName copy("(((#{toReturn actorType}) (#{toReturn actorName}->entity))->#{actor actorName})" interpolate)
			toReturn actorType = actor actorType
			toReturn properties = actor properties
		)
		TableOfSymbols ensureKnownClassForClass(toReturn actorType, Translator currentClassName)
	)
	toReturn
)

Actor getReturnedType := method(action,
	candidate := TableOfSymbols classMethods at(action getActionType(self) actorType) at(action actionName)
	if(candidate isNil,
		candidate = Actor unnamedActor(self actorType)
	)
	candidate
)

Actor getCreatorSignature := method(
	"Object #{self actorType}_Create(void)" interpolate
)

Actor getCreatorBody := method(
	toReturn := list(
		"{\n",
		"\tObject _self = Object_Create();\n",
		"\tDPUSHS (\"#{self actorType}: Create begined.\")\n" interpolate,
		"\t_self->entity = Allocator_New(_allocator, sizeof(struct #{self actorType}));\n" interpolate,
		"\t_self->gid = #{TableOfSymbols getClassId(self actorType)};\n" interpolate,
		"\t_self->destroy = &#{Action with(Token with(\"Destroy\")) getActionType(self) actorType}_Destroy;\n" interpolate
	)
	
	TableOfSymbols classFields at(actorType) foreach(field,
		toReturn push("\t((#{actorType}) (_self->entity))->#{field actorName} = _nil;\n" interpolate)
	)
	if(TableOfSymbols actorHasAction(Actor unnamedActor(self actorType), Action with("Init")),
		toReturn push("\t_self = #{self actorType}_Init(_self);\n" interpolate)
	)
	toReturn push(
		"\tDPOPS (\"#{self actorType}: Create ended.\")\n" interpolate,
		"\treturn _self;\n",
		"}\n"
	)
	
	toReturn join
)

Actor getInitializeClassBody := method(
	toReturn := list(
		"\nvoid #{actorType}_InitializeClass()\n" interpolate,
		"{\n",
		"\tINITIALIZE_CLASS(#{actorType}_InitializeClass);" interpolate,
		"\tObject _className = StringFactory_FromUTF8(_stringFactory, \"#{actorType}\", #{actorType size});\n" interpolate,
		"\tObject _gid = NumberFactory_FromLong(_numberFactory, #{actorType}GID);\n" interpolate
	)
	
	actorParentType := TableOfSymbols mapOfClassParents at(actorType)
	if(actorParentType != nil,
		toReturn push(
			"\tObject _parentClassName = StringFactory_FromUTF8(_stringFactory, \"#{actorParentType}\", #{actorParentType size});\n" interpolate,
			"\tSuperClass_RegisterClassWithNameWithGIDWithParentClassName(_superClass, _className, _gid, _parentClassName);\n"
		),
		
		toReturn push(
			"\tSuperClass_RegisterClassWithNameWithGIDWithParentClassName(_superClass, _className, _gid, _nil);\n"
		)
	)
	
	TableOfSymbols classMethods at(actorType) foreach(methodName, methodResultClass,
		toReturn append("\tSuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &#{actorType}_#{methodName}), StringFactory_FromUTF8(_stringFactory, \"#{methodName}\", #{methodName size}), _className);\n" interpolate)
	)
	TableOfSymbols mapOfMethodAliases at(actorType) foreach(methodName, realMethodName,
		toReturn append("\tSuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &#{actorType}_#{realMethodName}), StringFactory_FromUTF8(_stringFactory, \"#{methodName asMutable escape}\", #{methodName size}), _className);\n" interpolate)
	)
	toReturn append("}")
	
	toReturn join
)

Actor setProperty := method(property,
	properties appendIfAbsent(property)
	self
)

Actor hasProperty := method(property,
	properties contains(property)
)
