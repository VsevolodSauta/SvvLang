Line := Object clone
Line string := nil

Line withString := method(argument,
	toReturn := Line clone
	toReturn string = argument 
	toReturn removeComments
	toReturn
)

Line removeComments := method(
	string = string ?beforeSeq("//")
)

tokens := lazySlot(
	toReturn := self string ?splitNoEmpties
	toReturn ?foreach(token, token appendProto(Token))
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

Line translateMethodEntryLine := method(
	DestinationFile write(tokens join)
)
