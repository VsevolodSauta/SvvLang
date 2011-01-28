<Stack> <List> [Retain] list

Stack Init
	self.list = <List>
	return self

Stack Push object
	self.list PushBack object
	return self

Stack <Object> Pop
	return self.list PopBack

Stack <Object> Remove
	return self.list RemoveBack

Stack <Object> Peek
	return self.list PeekBack

Stack <Logic> Empty (IsEmpty)
	return self.list Empty

Stack <Comparation> Compare <Stack> stack
	return (self.list) ? (stack.list)

Stack <Object> Destroy
	self.list Release
	return (self AsObject) Destroy

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

