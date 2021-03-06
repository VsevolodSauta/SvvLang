<ListIterator@Object> <List> [Retain] list <ListNode> [Retain] node <Logic> system

ListIterator <Comparison> CompareSameGID <ListIterator> iterator
	return self.node ? iterator.node

ListIterator Destroy
	self.node Release
	if self.system Not
		self.list Release
	return super Destroy

ListIterator Clone
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	toReturn.system = false
	return toReturn

ListIterator DeepClone
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	toReturn.system = false
	return toReturn

ListIterator InitWithListAndNode <List> list <ListNode> node
	self.list = list
	self.node = node
	self.system = false
	return self

ListIterator SystemInitWithListAndNode <List> list <ListNode> node
	self.list = list
	self.node = node
	self.system = true
	list Release
	return self

ListIterator ResetNode <ListNode> node
	self.node = node
	return self

ListIterator Hide
	self.node = nil
	return self

ListIterator Hidden
	return self.node == nil

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
			currentPosition Inc
	else
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

ListIterator SearchForwardExactlySame object
	while self NotThisEnd
		if (self ThisData) Is object
			break
		self Next
	return self

ListIterator SearchBackwardExactlySame object
	while self NotThisBegin
		if (self ThisData) Is object
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

ListIterator ThisRemove (Remove RemoveThis)		// Здесь все правильно. :)
	self.node.next.prev = self.node.prev		// Node объявлена со свойством Retain.
	self.node.prev.next = self.node.next
	self.node Release
	return self

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

ListIterator <Logic> LogicData
	return self.node.data AsLogic

ListIterator <Number> NumberData
	return self.node.data AsNumber

ListIterator <List> ListData
	return self.node.data AsList

ListIterator <ListMap> ListMapData
	return self.node.data AsListMap

ListIterator <Char> CharData
	return self.node.data AsChar

ListIterator ThisSetData (SetThisData SetData) object
	self.node.data = object
	return self

ListIterator PrevSetData (SetPrevData) object
	self.node.prev.data = object
	return self

ListIterator NextSetData (SetNextData) object
	self.node.next.data = object
	return self

ListIterator AddAfter object
	addingElement = <ListNode>
	addingElement.data = object
	savedNext = self.node.next
	self.node.next = addingElement
	addingElement.prev = self.node
	addingElement.next = savedNext
	savedNext.prev = addingElement
	return self

ListIterator AddBefore object
	addingElement = <ListNode>
	addingElement.data = object
	savedPrev = self.node.prev
	self.node.prev = addingElement
	addingElement.next = self.node
	addingElement.prev = savedPrev
	savedPrev.next = addingElement
	return self

ListIterator <Logic> ThisBegin (Begin)
	return self.node.prev == nothing

ListIterator <Logic> ThisEnd (End)
	return self.node.next == nothing

ListIterator <Logic> PrevBegin
	return self.node.prev.prev == nothing

ListIterator <Logic> NextEnd
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

ListIterator AddListBeforeClonning <List> list
	listIterator = list First
	while listIterator NotThisEnd
		self AddBefore (((listIterator ThisData) DynamicallyClone) Autorelease)
		listIterator Next
	return self

ListIterator AddListAfterClonning <List> list
	listIterator = list Last
	while listIterator NotThisBegin
		self AddAfter (((listIterator ThisData) DynamicallyClone) Autorelease)
		listIterator Prev
	return self

ListIterator AddListBeforeDeepClonning <List> list
	listIterator = list First
	while listIterator NotThisEnd
		self AddBefore (((listIterator ThisData) DynamicallyDeepClone) Autorelease)
		listIterator Next
	return self

ListIterator AddListAfterDeepClonning <List> list
	listIterator = list Last
	while listIterator NotThisBegin
		self AddAfter (((listIterator ThisData) DynamicallyDeepClone) Autorelease)
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

ListIterator StringSkipSpace
	while (self CharData) IsSpace
		self ++
	return self

ListIterator StringSkipWhiteSpace
	while (self CharData) IsWhiteSpace
		self ++
	return self
