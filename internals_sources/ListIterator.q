<ListIterator> <List> list <ListNode> node

ListIterator <Logic> Compare <ListIterator> iterator
	return self.node Compare iterator.node

ListIterator Destroy
	self.node Release
	self.list Release
	return (self AsObject) Destroy

ListIterator Clone
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	toReturn.list Retain
	toReturn.node Retain
	return toReturn

ListIterator InitWithNodeAndList <List> list <ListNode> node
	list Retain
	node Retain
	self.list = list
	self.node = node
	return self

ListIterator ResetNode
	node Retain
	self.node Release
	self.node = node
	return self

ListIterator Hide
	return self ResetNode self.list.head

ListIterator Next
	return self ResetNode self.node.next

ListIterator Prev
	return self ResetNode self.node.prev

ListIterator ToBegin
	return self ResetNode self.list.head.next

ListIterator ToBegin
	return self ResetNode self.list.tail.prev

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
	quantity = positionTo - positionFrom
	while quantity < 0
		self Prev
		quantity Inc
	while quantity > 0
		self Next
		quantity Dec
	return self

ListIterator SearchForward object
	while self NotThisEnd
		if self ThisData == object
			break
		self Next
	return self

ListIterator <Number> SearchForwardOffset object
	toReturn = 0
	while self NotThisEnd
		if (self ThisData) == object
			return position
		self Next
		position Inc
	return -1

ListIterator ThisRemove
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

ListIterator <Object> ThisData
	return self.node.data

ListIterator <Object> NextData
	return self.node.next.data

ListIterator <Object> PrevData
	return self.node.prev.data

ListIterator ThisSetData object
	object Retain
	self.node.data Release
	self.node.data = object
	return self

ListIterator PrevSetData object
	object Retain
	self.node.prev.data Release
	self.node.prev.data = object
	return self

ListIterator NextSetData object
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

ListIterator ThisBegin
	return self.node.prev == nothing

ListIterator ThisEnd
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
		self.node release
		self Next
		deletedCount Inc
	self.node.prev = savedPrev
	savedPrev.next = self.node
	return self

