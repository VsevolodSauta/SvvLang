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
	return (self AsObject) Destroy

List Clone
	list = <List>
	list.iterator ToEnd
	list.iterator AddListAfter self
	list.iterator Hide
	return list

List <Comparation> Compare <List> list
	self.iterator ToBegin
	list.iterator ToBegin
	loop
		if self.iterator ThisEnd
			if list.iterator ThisEnd
				return equal
			else
				return less
		if list.iterator ThisEnd
			return greater
		candidateForReturning = (self.iterator ThisData) Compare (list.iterator ThisData)
		if candidateForReturning == equal
			list.iterator Next
			self.iterator Next
		else
			return candidateForReturning

List Clean
	node = self.head.next
	while node != self.tail
		nextNode = node.next
		node Release
		node = nextNode
	self.head.next = self.tail
	self.tail.prev = self.head
	return self

List PushFront object
	self.iterator ToBegin
	self.iterator AddBefore object
	self.iterator Hide
	return self

List PushBack object
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
	def self.iterator ThisData
	self.iterator ThisRemove
	self.iterator Hide

List <Object> PopBack
	self.iterator ToEnd
	def self.iterator ThisData
	self.iterator ThisRemove
	self.iterator Hide

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

List RemoveLast object
	self.iterator ToEnd
	self.iterator SearchBackward object
	if self.iterator NotThisBegin
		self.iterator ThisRemove
	self.iterator Hide
	return self

List RemoveEvery object
	self.iterator ToBegin
	self.iterator SearchForward object
	while self.iterator NotThisEnd
		self.iterator ThisRemove
		self.iterator SearchForward object
	self.iterator Hide
	return self

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
	iterator SystemInitWithListAndNode self self.head
	return iterator

List <Object> DataFromPosition <Number> position
	self.iterator ToPosition position
	def self.iterator ThisData
	self.iterator Hide

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
	self.iterator ToBegin
	toReturn = 0
	while self.iterator NotThisEnd
		toReturn Inc
		self.iterator Next
	self.iterator Hide
	return toReturn

List Concatenate <List> list
	self.iterator ToEnd
	self.iterator AddListAfter list
	self.iterator Hide
	return self

List SortInPlace
	return self
