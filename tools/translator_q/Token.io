Token := Sequence clone

Token isCreator := method(
	(self beginsWithSeq("<")) and (self endsWithSeq(">"))
)

Token isGlobalObjectDefinition := method(
	self beginsWithSeq("@")
)

Token with := method(sequence,
	toReturn := sequence clone
	toReturn appendProto(Token)
)

Token outOfBrackets := method(
	self exclusiveSlice(1, self size - 1)
)

Token className := method(
	self outOfBrackets split("@") first
)

Token isKeyword := method(
	TableOfSymbols isKeyword(self)
)

Token looksLikeMethodDefinition := method(
	((self isCreator) or (self isGlobalObjectDefinition)) not
)

Token looksLikeClass := method(
	((self asCapitalized) == self) and (self at(0) isLetter)
)

Token looksLikeIdentifier := method(
	((((self asCapitalized) == self) or isKeyword) not) or isCreator or isString or isChar or isPointer or (self at(0) isDigit)
)

Token looksLikeMethod := method(
	(looksLikeIdentifier or isKeyword) not
)

Token asKeyword := method(
	Keyword with(self)
)

Token asAction := method(
	Action with(self)
)

Token asActor := method(
	Actor with(self)
)

Token beginsNewAction := method(
	self == "("
)

Token endsNewAction := method(
	self == ")"
)

Token beginsPropertyList := method(
	self == "["
)

Token endsPropertyList := method(
	self == "]"
)

Token beginsString := method(
	(self beginsWithSeq("\""))
)

Token endsString := method(
	(self endsWithSeq("\""))
)

Token isNumber := method(
	self foreach(index, elem, 
		if((index == 0) and (elem == 45), continue)
		if((elem < 48) or (elem > 57), return false)
	)
	true
)

Token isString := method(
	(self beginsWithSeq("\"")) and (self endsWithSeq("\""))

)

Token isChar := method(
	(self beginsWithSeq("'")) and (self endsWithSeq("'"))
)

Token isPointer := method(
	self beginsWithSeq("&")
)
