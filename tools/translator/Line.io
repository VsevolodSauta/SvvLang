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

Line putMethodSignature := method(
	DestinationFile write("Method")
)

Line putMethodEntryLine := method(
	DestinationFile write(tokens join)
)