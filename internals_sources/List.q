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
	self.iterator ToBegin
	self.iterator AddBefore object
	self.iterator Hide
	return self

List PushBack (Append Push) object
	self.iterator ToEnd
	self.iterator AddAfter object
	self.iterator Hide
	return self

List PushSorted object
	self.iterator ToBegin
	while (self.iterator NotThisEnd) And ((self.iterator ThisData) < (object))
		self.iterator Next
	self.iterator AddBefore object
	self.iterator Hide
	return self

List <Object> PeekFront
	self.iterator ToBegin
	def self.iterator ThisData
	self.iterator Hide

List <Object> PeekBack
	self.iterator ToEnd
	def self.iterator ThisData
	self.iterator Hide

List <Object> PopFront
	self.iterator ToBegin
	def ((self.iterator ThisData) Retain) Autorelease
	self.iterator ThisRemove
	self.iterator Hide

List <Object> PopBack (Pop)
	self.iterator ToEnd
	def ((self.iterator ThisData) Retain) Autorelease
	self.iterator ThisRemove
	self.iterator Hide

List <Object> RemoveFront
	self.iterator ToBegin
	self.iterator ThisRemove
	self.iterator Hide
	return self

List <Object> RemoveBack (Remove)
	self.iterator ToEnd
	self.iterator ThisRemove
	self.iterator Hide
	return self

List AddAfterPosition <Number> position object
	self.iterator ToPosition position
	self.iterator AddAfter object
	self.iterator Hide
	return self

List AddBeforePosition <Number> position object
	self.iterator ToPosition position
	self.iterator AddBefore object
	self.iterator Hide
	return self

List <Logic> Contains object
	self.iterator ToBegin
	self.iterator SearchForward object
	def self.iterator NotThisEnd
	self.iterator Hide

List RemoveFirst object
	self.iterator ToBegin
	self.iterator SearchForward object
	if self.iterator NotThisEnd
		self.iterator ThisRemove
	self.iterator Hide
	return self

List <Logic> RemoveFirstWithConfirmation object
	confirmation = false
	self.iterator ToBegin
	self.iterator SearchForward object
	if self.iterator NotThisEnd
		confirmation = true
		self.iterator ThisRemove
	self.iterator Hide
	return confirmation

List RemoveLast object
	self.iterator ToEnd
	self.iterator SearchBackward object
	if self.iterator NotThisBegin
		self.iterator ThisRemove
	self.iterator Hide
	return self

List RemoveLastWithConfirmation object
	confirmation = false
	self.iterator ToEnd
	self.iterator SearchBackward object
	if self.iterator NotThisBegin
		confirmation = true
		self.iterator ThisRemove
	self.iterator Hide
	return confirmation

List RemoveEvery object
	self.iterator ToBegin
	self.iterator SearchForward object
	while self.iterator NotThisEnd
		self.iterator ThisRemove
		self.iterator SearchForward object
	self.iterator Hide
	return self

List RemoveEveryWithConfirmation object
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

List <Object> ObjectAtPosition (ObjectFromPosition DataFromPosition) <Number> position
	self.iterator ToPosition position
	def self.iterator ThisData
	self.iterator Hide

List <Object> ObjectAtPositionIfExists (ObjectAtPositionIfPossible) <Number> position
	if (self Size) > position
		return self ObjectAtPosition position
	else
		return nil

List <ListMap> ListMapAtPosition (ListMapFromPosition) <Number> position
	return (self ObjectAtPosition 0) AsListMap

List Search object
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
	self.iterator ToBegin
	def self.iterator ThisEnd
	self.iterator Hide

List Concatenate <List> list
	self.iterator ToEnd
	self.iterator AddListAfter list
	self.iterator Hide
	return self

List SortInPlace
	return self
