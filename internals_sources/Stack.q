<Stack> <List> list

Stack Init
	self.list = <List>
	return self

Stack Push object
	self.list PushBack object
	return self

Stack <Object> Pop
	return self.list PopBack

Stack <Object> Peek
	return self.list PeekBack

Stack <Comparation> Compare <Stack> queue
	return (self.list Hash) Compare (queue.list Hash)

Stack <Object> Destroy
	self.list Destroy
	return (self AsObject) Destroy

Stack <List> GetList
	return self.list TempClone

Stack Clone
	toReturn = <Stack>
	toReturn.list Release
	toReturn.list = self.list Clone
	return toReturn

