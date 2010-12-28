<Stack> <List> [Retain] list

Stack Init
	DEBUG_PUSH ("Stack: Initing.")
	self.list = <List>
	DEBUG_POP ("Stack: Inited.")
	return self

Stack Push object
	DEBUG_PUSH ("Stack: Pushing.")
	self.list PushBack object
	DEBUG_POP ("Stack: Pushed.")
	return self

Stack <Object> Pop
	DEBUG_PUSH ("Stack: Popping.")
	def self.list PopBack
	DEBUG_POP ("Stack: Popped.")

Stack <Object> Peek
	DEBUG_PUSH ("Stack: Peeking.")
	def self.list PeekBack
	DEBUG_POP ("Stack: Peeked.")

Stack <Logic> Empty (IsEmpty)
	return self.list Empty

Stack <Comparation> Compare <Stack> stack
	return (self.list Hash) Compare (stack.list Hash)

Stack <Object> Destroy
	DEBUG_PUSH ("Stack: Destroying.")
	self.list Release
	DEBUG_POP ("Stack: Destroyed.")
	return (self AsObject) Destroy

Stack <List> GetList
	return self.list TempClone

Stack Clone
	toReturn = <Stack>
	toReturn.list = self.list Clone
	return toReturn

