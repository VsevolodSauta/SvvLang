<ListMapIterator> <ListMap> [Retain] listMap <List> [Retain] key <Stack> elementStack <Logic> thisEnd <Logic> thisBegin

ListMapIterator Init
	self.elementStack = <Stack>
	self.key = <List>
	return self

ListMapIterator SetListMap <ListMap> listMap
	self.listMap = listMap
	return self 

ListMapIterator ToBegin
	self.key Clean
	self.thisEnd = no
	self.thisBegin = no
	element = <ListMapIteratorElement>
	element.node = self.listMap.root
	element.iterator = (element.node.nextMap First) --
	element.nextExists = (self MoreThanOneElementInNode element.node)
	element.prevExists = no
	self.elementStack Push element
	element Release
	if element.node.mapped
		return self
	if element.node.nextMap Empty
		self.thisBegin = yes
		self.thisEnd = yes
		return self
	while element.node.mapped Not
		element = self NextAnyWithElement element
	return self

ListMapIterator <Logic> MoreThanOneElementInNode <ListMapNode> node
	if node.mapped And (node.nextMap NotEmpty)
		return true
	return (node.nextMap Size) > 1

ListMapIterator Next (++) // Подразумевается, что он есть.
	if self.thisBegin
		if self.thisEnd Not
			self.thisBegin = no
		return self
	element = (self.elementStack Pop) AsListMapIteratorElement
	if element.nextExists Not
		self.elementStack Push element
		self.thisEnd = yes
		return self
	while element.iterator NextEnd
		element = (self.elementStack Pop) AsListMapIteratorElement
		self.key RemoveBack
	self.elementStack Push element
	element = self NextAnyWithElement element
	while element.node.mapped Not
		element = self NextAnyWithElement element
	return self

ListMapIterator <ListMapIteratorElement> NextAnyWithElement <ListMapIteratorElement> element
	nextElement = <ListMapIteratorElement>
	nextElement.node = element AdvancingValue (self.elementStack ObjectAtPositionIfExists 1)
	nextElement.iterator = (nextElement.node.nextMap First) --
	nextElement.nextExists = (element.nextExists) Or (self MoreThanOneElementInNode nextElement.node)
	nextElement.prevExists = element.prevExists
	self.elementStack Push nextElement
	nextElement Release
	self.key PushBack (element.iterator ThisKey)
	return nextElement

ListMapIterator ThisRemoveRight (RemoveThis ThisRemove)
	assert "" self.thisEnd != true
	assert "" self.thisBegin != true
	key = self.key
	self ++
	self.listMap Remove key
	return self

ListMapIterator ThisRemoveLeft
	assert "" self.thisEnd != true
	assert "" self.thisBegin != true
	key = self.key
	self --
	self.listMap Remove key
	return self

ListMapIterator <List> ThisKey (Key)
	return (self.key Clone) Autorelease

ListMapIterator <Object> ThisValue (ThisData Value Data)
	element = (self.elementStack Peek) AsListMapIteratorElement
	return element.node.mapping

ListMapIterator <ListMap> ListMapData
	return (self ThisValue) AsListMap

ListMapIterator <List> ListData
	return (self ThisValue) AsList

ListMapIterator <Number> NumberData
	return (self ThisValue) AsNumber

ListMapIterator <Logic> LogicData
	return (self ThisValue) AsLogic

ListMapIterator ToEnd
	self.key Clean
	self.thisEnd = no
	self.thisBegin = no
	element = <ListMapIteratorElement>
	element.node = self.listMap.root
	element.iterator = (element.node.nextMap Last) ++
	element.prevExists = (self MoreThanOneElementInNode element.node)
	element.nextExists = no
	self.elementStack Push element
	element Release
	if element.node.nextMap Empty
		if element.node.mapped Not
			self.thisBegin = yes
			self.thisEnd = yes
		return self
	while element.iterator NotThisBegin // На выходе нода должна оказаться замапленной.
		element = self PrevAnyWithElement element
	return self

ListMapIterator Prev (--)
	if self.thisEnd
		if self.thisBegin Not
			self.thisEnd = no
		return self
	element = (self.elementStack Pop) AsListMapIteratorElement
	if element.prevExists Not
		self.elementStack Push element
		self.thisBegin = yes
		return self
	while element.iterator PrevBegin
		element = (self.elementStack Pop) AsListMapIteratorElement
		self.key RemoveBack
	self.elementStack Push element
	element = self PrevAnyWithElement element
	while element.node.mapped Not
		element = self PrevAnyWithElement element
	return self

ListMapIterator <ListMapIteratorElement> PrevAnyWithElement <ListMapIteratorElement> element
	nextElement = <ListMapIteratorElement>
	nextElement.node = element ReturningValue (self.elementStack ObjectAtPositionIfExists 1)
	nextElement.iterator = (nextElement.node.nextMap Last) ++
	nextElement.nextExists = element.nextExists
	nextElement.prevExists = element.prevExists Or (self MoreThanOneElementInNode nextElement.node)
	self.elementStack Push nextElement
	nextElement Release
	self.key PushBack (element.iterator ThisKey)
	return nextElement


ListMapIterator ThisEnd
	return self.thisEnd

ListMapIterator ThisBegin
	return self.thisBegin

ListMapIterator <Comparison> Compare <ListMapIterator> iterator
	candidate = self.listMap ? iterator.listMap
	if candidate == equal
		candidate = self.elementStack ? iterator.elementStack
	return candidate

ListMapIterator Clone
	toReturn = <ListMapIterator>
	toReturn.listMap = self.listMap
	toReturn.elementStack = self.elementStack DeepClone
	toReturn.thisBegin = self.thisBegin
	toReturn.thisEnd = self.thisEnd
	toReturn.key = self.key DeepClone
	return toReturn

ListMapIterator DeepClone
	toReturn = <ListMapIterator>
	toReturn.listMap = self.listMap
	toReturn.elementStack = self.elementStack DeepClone
	toReturn.thisBegin = self.thisBegin
	toReturn.thisEnd = self.thisEnd
	toReturn.key = self.key DeepClone
	return toReturn

ListMapIterator Destroy
	self.listMap Release
	self.elementStack Release
	return self Destroy
