Actor := Object clone
Actor actorType := "Object" asMutable clone
Actor actorName := Token clone

Actor clone := method(
	toReturn := Object super(clone)
	toReturn actorType := Actor actorType clone
	toReturn actorName := Actor actorName clone
	toReturn
)

Actor unnamedActor := method(unnamedActorType,
	toReturn := Actor clone
	toReturn actorName copy("[unnamed]")
	toReturn actorType copy(unnamedActorType)
	toReturn
)

Actor fullActor := method(fullActorName, fullActorType,
	toReturn := Actor clone
	toReturn actorName copy(fullActorName)
	toReturn actorType copy(fullActorType)
	toReturn
)

Actor with := method(name,
	toReturn := Actor clone
	
	if(name isCreator,
		toReturn actorType = name outOfBrackets
		TableOfSymbols ensureKnownClassForClass(toReturn actorType, "Object")
		toReturn actorName copy("#{toReturn actorType}_Create()" interpolate)
		return toReturn
	)
	
	if(name isNumber,
		toReturn actorType = "Number"
		toReturn actorName copy("NumberFactory_FromLong(numberFactory, #{name})" interpolate)
		return toReturn
	)
			
	listOfFields := name split(".")
	listOfFields foreach(index, field,
		if(index == 0,
			toReturn actorName copy(field)
			toReturn actorType = TableOfSymbols getActorType(field)
			if(toReturn actorType isNil,
				if(listOfFields size != 1, Exception raise("No fields in object #{field} of Object type found." interpolate))
				toReturn actorType = "Object"
				TableOfSymbols setActorType(toReturn)
				Translator insertDeclaration(field)
			),
			
			toReturn actorName copy("(((#{toReturn actorType}) (#{toReturn actorName}->entity))->#{field})" interpolate)
			toReturn actorType = TableOfSymbols getFieldType(toReturn actorType, field)
		)
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
		"\ttoReturn->entity = Allocator_New(allocator, sizeof(struct #{self actorType}));\n" interpolate,
		"\ttoReturn->gid = #{TableOfSymbols getClassId(self actorType)};\n" interpolate,
		"\tObject_SetComparator(toReturn, &#{self actorType}_Compare);\n" interpolate,
		"\tObject_SetDestructor(toReturn, &#{self actorType}_Destroy);\n" interpolate,
		"\tObject_SetCloner(toReturn, &#{self actorType}_Clone);\n" interpolate
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
