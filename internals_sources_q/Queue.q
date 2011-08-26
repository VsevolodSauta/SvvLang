<Queue> <List> [Retain] list

Queue Init
	self.list = <List>
	return self

Queue Push (Add Insert) object
	self.list PushBack object
	return self

Queue <Object> Pop
	return self.list PopFront

Queue <Object> PopIfNotEmpty
	if self IsEmpty
		return nil
	else
		return self Pop

Queue <Object> Remove
	return self.list RemoveFront

Queue <Object> RemoveIfNotEmpty
	if self IsEmpty
		return nil
	else
		return self Remove

Queue <Object> Peek
	return self.list PeekFront

Queue <Logic> Empty (IsEmpty)
	return self.list Empty

Queue <Comparison> Compare <Queue> queue
	return (self.list) ? (queue.list)

Queue <Object> Destroy
	self.list Release
	return self Destroy

Queue <List> GetList
	return (self.list Clone) Autorelease

Queue Clone
	toReturn = <Queue>
	toReturn.list = self.list Clone
	return toReturn

Queue DeepClone
	toReturn = <Queue>
	toReturn.list = self.list DeepClone
	return toReturn

