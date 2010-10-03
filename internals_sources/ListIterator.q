<ListIterator> <List> [Retain] list <ListNode> [Retain] node

ListIterator <Comparation> Compare <ListIterator> iterator
	return self.node ? iterator.node

ListIterator Destroy
	self.node Release
	self.list Release
	return (self AsObject) Destroy

ListIterator Clone
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	return toReturn

ListIterator InitWithListAndNode <List> list <ListNode> node
	self.list = list
	self.node = node
	return self

ListIterator SystemInitWithListAndNode <List> list <ListNode> node
	self.list = list
	self.node = node
	list Release
	return self

ListIterator ResetNode <ListNode> node
	self.node = node
	return self

ListIterator Hide
	self.node = self.list.head
	return self

ListIterator Next (++)
	self.node = self.node.next
	return self

ListIterator Prev (--)
	self.node = self.node.prev
	return self

ListIterator ToBegin
	self.node = self.list.head.next
	return self

ListIterator ToEnd
	self.node = self.list.tail.prev
	return self

ListIterator ToPosition <Number> position
	if position >= 0
		self ToBegin
		currentPosition = 0
		while currentPosition < position
			self Next
			position Inc
		return self
	self ToEnd
	currentPosition = -1
	while currentPosition > position
		currentPosition Dec
		self Prev
	return self

ListIterator FromPositionToPosition <Number> positionFrom <Number> positionTo
	quantity = positionTo Sub positionFrom
	while quantity < 0
		self Prev
		quantity Inc
	while quantity > 0
		self Next
		quantity Dec
	return self

ListIterator SearchForward object
	while self NotThisEnd
		if (self ThisData) == object
			break
		self Next
	return self

ListIterator SearchBackward object
	while self NotThisBegin
		if (self ThisData) == object
			break
		self Prev
	return self

ListIterator <Number> SearchForwardOffset object
	position = 0
	while self NotThisEnd
		if (self ThisData) == object
			return position
		self Next
		position Inc
	return -1

ListIterator ThisRemove (Remove)
	self.node.next.prev = self.node.next
	self.node.prev.next = self.node.prev
	self.node Release
	return self Next

ListIterator PrevRemove
	toRemove = self.node.next
	toRemove.next.prev = toRemove.prev
	toRemove.prev.next = toRemove.next
	toRemove Release
	return self

ListIterator NextRemove
	toRemove = self.node.prev
	toRemove.next.prev = toRemove.prev
	toRemove.prev.next = toRemove.next
	toRemove Release
	return self

ListIterator <Object> ThisData (Data)
	return self.node.data

ListIterator <Object> NextData
	return self.node.next.data

ListIterator <Object> PrevData
	return self.node.prev.data

ListIterator ThisSetData (SetThisData SetData) object
	object Retain
	self.node.data Release
	self.node.data = object
	return self

ListIterator PrevSetData (SetPrevData) object
	object Retain
	self.node.prev.data Release
	self.node.prev.data = object
	return self

ListIterator NextSetData (SetNextData) object
	object Retain
	self.node.next.data Release
	self.node.next.data = object
	return self

ListIterator AddAfter object
	object Retain
	addingElement = <ListNode>
	addingElement.data = object
	savedNext = self.node.next
	self.node.next = addingElement
	addingElement.prev = self.node
	addingElement.next = savedNext
	savedNext.prev = addingElement
	return self

ListIterator AddBefore object
	object Retain
	addingElement = <ListNode>
	addingElement.data = object
	savedPrev = self.node.prev
	self.node.prev = addingElement
	addingElement.next = self.node
	addingElement.prev = savedPrev
	savedPrev.next = addingElement
	return self

ListIterator ThisBegin (Begin)
	return self.node.prev == nothing

ListIterator ThisEnd (End)
	return self.node.next == nothing

ListIterator PrevBegin
	return self.node.prev.prev == nothing

ListIterator NextEnd
	return self.node.next.next == nothing

ListIterator AddListBefore <List> list
	listIterator = list First
	while listIterator NotThisEnd
		self AddBefore (listIterator ThisData)
		listIterator Next
	return self

ListIterator AddListAfter <List> list
	listIterator = list Last
	while listIterator NotThisBegin
		self AddAfter (listIterator ThisData)
		listIterator Prev
	return self

ListIterator RemoveCount <Number> count
	savedPrev = self.node.prev
	deletedCount = 0
	while deletedCount < count
		self.node Release
		self Next
		deletedCount Inc
	self.node.prev = savedPrev
	savedPrev.next = self.node
	return self

