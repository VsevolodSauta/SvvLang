Token := Object clone

Token isCreator := method(
	(self exclusiveSlice(0, 1) == "<") and (self exclusiveSlice(self size - 1, self size))
)

Token outOfBrackets := method(
	self exclusiveSlice(1, self size - 1)
)