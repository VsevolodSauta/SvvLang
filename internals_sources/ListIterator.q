<ListIterator> <List> [Retain] list <ListNode> [Retain] node <Logic> system

ListIterator <Comparation> Compare <ListIterator> iterator
	return self.node ? iterator.node

ListIterator Destroy
	self.node Release
	if self.system Is false
		self.list Release
	return (self AsObject) Destroy

ListIterator Clone
	DEBUG_PUSH ("List Iterator: Cloning.")
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	toReturn.system = false
	DEBUG_POP ("List Iterator: Clonned.")
	return toReturn

ListIterator DeepClone
	DEBUG_PUSH ("List Iterator: Deep cloning.")
	toReturn = <ListIterator>
	toReturn.list = self.list
	toReturn.node = self.node
	toReturn.system = false
	DEBUG_POP ("List Iterator: Deep clonned.")
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
	DEBUG_MSG ("List Iterator: Reseting node.")
	self.node = node
	return self

ListIterator Hide
	DEBUG_PUSH ("List Iterator: Hiding.")
	self.node = nil
	DEBUG_POP ("List Iterator: Hidden.")
	return self

ListIterator Next (++)
	DEBUG_MSG ("List Iterator: Advancing.")
	self.node = self.node.next
	return self

ListIterator Prev (--)
	DEBUG_MSG ("List Iterator: Returning.")
	self.node = self.node.prev
	return self

ListIterator ToBegin
	DEBUG_MSG ("List Iterator: Bringing to begin.")
	self.node = self.list.head.next
	return self

ListIterator ToEnd
	DEBUG_MSG ("List Iterator: Bringing to end.")
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

ListIterator ThisRemove (Remove)			// Здесь все правильно. :)
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
	DEBUG_MSG ("List Iterator: Getting this data.")
	return self.node.data

ListIterator <Object> NextData
	DEBUG_MSG ("List Iterator: Getting next data.")
	return self.node.next.data

ListIterator <Object> PrevData
	DEBUG_MSG ("List Iterator: Getting previous data.")
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
	DEBUG_MSG ("List Iterator: Setting this data.")
	self.node.data = object
	return self

ListIterator PrevSetData (SetPrevData) object
	DEBUG_MSG ("List Iterator: Setting previous data.")
	self.node.prev.data = object
	return self

ListIterator NextSetData (SetNextData) object
	DEBUG_MSG ("List Iterator: Setting next data.")
	self.node.next.data = object
	return self

ListIterator AddAfter object
	DEBUG_PUSH ("List Iterator: Adding data to the next.")
	addingElement = <ListNode>
	addingElement.data = object
	savedNext = self.node.next
	self.node.next = addingElement
	addingElement.prev = self.node
	addingElement.next = savedNext
	savedNext.prev = addingElement
	DEBUG_POP ("List Iterator: Data added to the next.")
	return self

ListIterator AddBefore object
	DEBUG_PUSH ("List Iterator: Adding data to the prev.")
	addingElement = <ListNode>
	addingElement.data = object
	savedPrev = self.node.prev
	self.node.prev = addingElement
	addingElement.next = self.node
	addingElement.prev = savedPrev
	savedPrev.next = addingElement
	DEBUG_POP ("List Iterator: Data added to the prev.")
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
		self AddBefore ((listIterator ThisData) Clone)
		listIterator Next
	return self

ListIterator AddListAfterClonning <List> list
	listIterator = list Last
	while listIterator NotThisBegin
		self AddAfter ((listIterator ThisData) Clone)
		listIterator Prev
	return self

ListIterator AddListBeforeDeepClonning <List> list
	listIterator = list First
	while listIterator NotThisEnd
		self AddBefore ((listIterator ThisData) DeepClone)
		listIterator Next
	return self

ListIterator AddListAfterDeepClonning <List> list
	listIterator = list Last
	while listIterator NotThisBegin
		self AddAfter ((listIterator ThisData) DeepClone)
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
