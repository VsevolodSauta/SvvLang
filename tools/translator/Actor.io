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
	toReturn := Actor clone
	
	if(name isCreator,
		toReturn actorType = name outOfBrackets
		TableOfSymbols ensureKnownClassForClass(toReturn actorType, "Object")
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
		toReturn actorName copy("StringFactory_FromUTF8(_stringFactory, \"#{name outOfBrackets asMutable escape}\", #{name outOfBrackets size})" interpolate)
		return toReturn
	)
	
	if(name isChar,
		toReturn actorType = "Char"
		toReturn actorName copy("CharFactory_FromLong(_charFactory, #{name})" interpolate)
		return toReturn
	)
	
	listOfFieldNames := name split(".")
	listOfFieldNames foreach(index, fieldName,
		fieldName = "_" .. fieldName
		if(index == 0,
			toReturn actorName copy(fieldName)
			toReturn actorType = TableOfSymbols getActorType(fieldName)
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
	TableOfSymbols getActorActionReturnedType(self, action)
)

Actor getCreatorSignature := method(
	"Object #{self actorType}_Create(void)" interpolate
)

Actor getCreatorBody := method(
	toReturn := list(
		"{\n",
		"\tObject toReturn = Object_Create();\n",
		"\ttoReturn->entity = Allocator_New(_allocator, sizeof(struct #{self actorType}));\n" interpolate,
		"\ttoReturn->gid = #{TableOfSymbols getClassId(self actorType)};\n" interpolate,
		"\tObject_SetComparator(toReturn, &#{self actorType}_Compare);\n" interpolate,
		"\tObject_SetDestructor(toReturn, &#{self actorType}_Destroy);\n" interpolate,
		"\tObject_SetCloner(toReturn, &#{self actorType}_Clone);\n" interpolate
	)
	TableOfSymbols classFields at(actorType) foreach(field,
		toReturn push("\t((#{actorType}) (toReturn->entity))->#{field actorName} = _nil;\n" interpolate)
	)
	if(TableOfSymbols actorHasAction(Actor unnamedActor(self actorType), Action with("Init")),
		toReturn push("\ttoReturn = #{self actorType}_Init(toReturn);\n" interpolate)
	)
	toReturn push(
		"\treturn toReturn;\n",
		"}\n"
	)
	
	toReturn join
)

Actor setProperty := method(property,
	properties appendIfAbsent(property)
	self
)

Actor hasProperty := method(property,
	properties contains(property)
)
