<Queue> <List> [Retain] list

Queue Init
	self.list = <List>
	return self

Queue Push (Add Insert) object
	self.list PushBack object
	return self

Queue <Object> Pop
	return self.list PopFront

Queue <Object> Peek
	return self.list PeekFront

Queue <Comparation> Compare <Queue> queue
	return (self.list) Compare (queue.list)

Queue <Object> Destroy
	self.list Destroy
	return (self AsObject) Destroy

Queue <List> GetList
	return self.list TempClone

Queue Clone
	toReturn = <Queue>
	toReturn.list = self.list Clone
	return toReturn

