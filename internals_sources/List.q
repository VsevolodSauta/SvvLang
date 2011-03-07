<List> <ListIterator> iterator <ListNode> head <ListNode> tail

List Init
	self.head = <ListNode>
	self.tail = <ListNode>
	self.head.next = self.tail
	self.tail.prev = self.head
	self.tail.next = self.head.prev = nil
	self.iterator = self SystemIterator
	return self

List Destroy
	self.iterator Release
	node = self.head
	while node != nil
		nextNode = node.next
		node Release
		node = nextNode
	return self Destroy

List Clone
	list = <List>
	list.iterator ToEnd
	list.iterator AddListAfter self
	list.iterator Hide
	return list

List DeepClone
	list = <List>
	list.iterator ToEnd
	list.iterator AddListAfterDeepClonning self
	list.iterator Hide
	return list

List <Comparation> Compare <List> list
	selfIterator = self First
	listIterator = list First
	loop
		if selfIterator ThisEnd
			if listIterator ThisEnd
				return equal
			else
				return less
		if listIterator ThisEnd
			return greater
		candidateForReturning = (selfIterator ThisData) ? (listIterator ThisData)
		if candidateForReturning == equal
			listIterator Next
			selfIterator Next
		else
			return candidateForReturning

List Clean (RemoveAll)
	node = self.head.next
	while node != self.tail
		nextNode = node.next
		node Release
		node = nextNode
	self.head.next = self.tail
	self.tail.prev = self.head
	return self

List PushFront (Prepend) object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator AddBefore object
	self.iterator Hide
	return self

List PushBack (Append Push) object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	self.iterator AddAfter object
	self.iterator Hide
	return self

List PushSorted object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	while (self.iterator NotThisEnd) And ((self.iterator ThisData) < (object))
		self.iterator Next
	self.iterator AddBefore object
	self.iterator Hide
	return self

List <Object> PeekFront
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	def self.iterator ThisData
	self.iterator Hide

List <Object> PeekBack
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	def self.iterator ThisData
	self.iterator Hide

List <Object> PopFront
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	def ((self.iterator ThisData) Retain) Autorelease
	self.iterator ThisRemove
	self.iterator Hide

List <Object> PopBack (Pop)
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	def ((self.iterator ThisData) Retain) Autorelease
	self.iterator ThisRemove
	self.iterator Hide

List <Object> RemoveFront
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator ThisRemove
	self.iterator Hide
	return self

List <Object> RemoveBack (Remove)
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	self.iterator ThisRemove
	self.iterator Hide
	return self

List PushBackIfAbsent (AppendIfAbsent) object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	while self.iterator NotThisEnd
		if (self.iterator ThisData) == object
			self.iterator Hide
			return self
		self.iterator ++
	self.iterator AddBefore object
	self.iterator Hide
	return self

List AddAfterPosition <Number> position object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToPosition position
	self.iterator AddAfter object
	self.iterator Hide
	return self

List AddBeforePosition (InsertAtPositionObject AtInsert) <Number> position object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToPosition position
	self.iterator AddBefore object
	self.iterator Hide
	return self

List <Object> ObjectAtPosition (ObjectFromPosition DataFromPosition) <Number> position
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToPosition position
	def self.iterator ThisData
	self.iterator Hide

List <Object> ObjectAtPositionIfExists (ObjectAtPositionIfPossible) <Number> position
	if (self Size) > position
		return self ObjectAtPosition position
	else
		return nil

List RemoveObjectAtPosition (RemoveAt) <Number> position
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToPosition position
	self.iterator RemoveThis
	self.iterator Hide
	return self

List ReplaceAtPositionWithObject <Number> position object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToPosition position
	self.iterator SetThisData object
	self.iterator Hide
	return self

List <Logic> Contains object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator SearchForward object
	def self.iterator NotThisEnd
	self.iterator Hide

List RemoveFirst object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator SearchForward object
	if self.iterator NotThisEnd
		self.iterator ThisRemove
	self.iterator Hide
	return self

List RemoveFirstExactlySame object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator SearchForwardExactlySame object
	if self.iterator NotThisEnd
		self.iterator ThisRemove
	self.iterator Hide
	return self

List <Logic> RemoveFirstWithConfirmation object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	confirmation = false
	self.iterator ToBegin
	self.iterator SearchForward object
	if self.iterator NotThisEnd
		confirmation = true
		self.iterator ThisRemove
	self.iterator Hide
	return confirmation

List RemoveLast object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	self.iterator SearchBackward object
	if self.iterator NotThisBegin
		self.iterator ThisRemove
	self.iterator Hide
	return self

List RemoveLastExactlySame object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	self.iterator SearchBackwardExactlySame object
	if self.iterator NotThisBegin
		self.iterator ThisRemove
	self.iterator Hide
	return self

List RemoveLastWithConfirmation object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	confirmation = false
	self.iterator ToEnd
	self.iterator SearchBackward object
	if self.iterator NotThisBegin
		confirmation = true
		self.iterator ThisRemove
	self.iterator Hide
	return confirmation

List RemoveEvery object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	self.iterator SearchForward object
	while self.iterator NotThisEnd
		self.iterator ThisRemove
		self.iterator SearchForward object
	self.iterator Hide
	return self

List RemoveEveryWithConfirmation object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	confirmation = false
	self.iterator ToBegin
	self.iterator SearchForward object
	while self.iterator NotThisEnd
		confirmation = true
		self.iterator ThisRemove
		self.iterator SearchForward object
	self.iterator Hide
	return confirmation

List <ListIterator> Last
	iterator = <ListIterator> Autorelease
	iterator InitWithListAndNode self self.tail.prev
	return iterator

List <ListIterator> First
	iterator = <ListIterator> Autorelease
	iterator InitWithListAndNode self self.head.next
	return iterator

List <ListIterator> SystemIterator
	iterator = <ListIterator>
	iterator SystemInitWithListAndNode self nil
	return iterator

List <ListMap> ListMapAtPosition (ListMapFromPosition) <Number> position
	return (self ObjectAtPosition position) AsListMap

List Search object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	list = <List> Autorelease
	self.iterator SearchForward object
	while self.iterator NotThisEnd
		list PushBack (self.iterator TempClone)
		self.iterator SearchForward object
	return list

List <ListIterator> IteratorFromPosition <Number> position
	return (self First) ToPosition position

List <ListIterator> CreatingIteratorFromPosition <Number> position
	iterator = self First
	currentPosition = 0
	while currentPosition <= position
		currentPosition Inc
		if iterator ThisEnd
			iterator AddBefore nil
		else
			iterator Next
	iterator Prev
	return iterator

List SearchPositions object
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	list = <List>
	self.iterator ToBegin
	position = 0
	while self.iterator NotThisEnd
		if (list.iterator ThisData) == object
			list PushBack (position TempClone)
		position Inc
		self.iterator Next
	self.iterator Hide
	return list

List SublistBetweenPositions <Number> positionFrom <Number> positionTo
	self.iterator ToPosition positionFrom
	list = <List> Autorelease
	position = positionFrom Clone
	while position <= positionTo
		list PushBack (self.iterator ThisData)
		self.iterator Next
		position Inc
	self.iterator Hide
	position Release
	return list

List SublistBetweenIterators <ListIterator> positionFrom <ListIterator> positionTo
	iterator = positionFrom Clone
	list = <List>
	while iterator != positionTo
		list PushBack (iterator ThisData)
		iterator Next
	iterator Release
	return list

List <Number> Size
	iterator = self.iterator Clone
	iterator ToBegin
	toReturn = 0
	while iterator NotThisEnd
		toReturn Inc
		iterator Next
	iterator Release
	return toReturn

List <Logic> Empty (IsEmpty)
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToBegin
	def self.iterator ThisEnd
	self.iterator Hide

List Concatenate <List> list
	assert "Список занят. Итератор не на месте." self.iterator Hidden
	self.iterator ToEnd
	self.iterator AddListAfter list
	self.iterator Hide
	return self
	
List Set (ReplaceWithList) <List> list
	self Clean
	self Concatenate list
	return self

List SortInPlace
	return self

List PrintLn
	console PrintLnString self
	return self

List Print
	console PrintString self
	return self


