Token := Sequence clone

Token isCreator := method(
	(self exclusiveSlice(0, 1) == "<") and (self exclusiveSlice(self size - 1, self size))
)

Token with := method(sequence,
	toReturn := sequence clone
	toReturn appendProto(Token)
)

Token outOfBrackets := method(
	self exclusiveSlice(1, self size - 1)
)

Token isKeyword := method(
	TableOfSymbols isKeyword(self)
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

