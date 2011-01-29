<Stack> <List> [Retain] list

Stack Init
	self.list = <List>
	return self

Stack Push object
	self.list PushFront object
	return self

Stack <Object> Pop
	return self.list PopFront

Stack <Object> Remove
	return self.list RemoveFront

Stack <Object> Peek
	return self.list PeekFront

Stack <Object> ObjectAtPositionIfExists <Number> position
	return self.list ObjectAtPositionIfExists position

Stack <Logic> Empty (IsEmpty)
	return self.list Empty

Stack Clean (Clear RemoveAll)
	self.list RemoveAll
	return self

Stack <Comparation> Compare <Stack> stack
	return (self.list) ? (stack.list)

Stack <Object> Destroy
	self.list Release
	return self Destroy

Stack <List> GetList
	return self.list TempClone

Stack Clone
	toReturn = <Stack>
	toReturn.list = self.list Clone
	return toReturn

Stack DeepClone
	toReturn = <Stack>
	toReturn.list = self.list DeepClone
	return toReturn

