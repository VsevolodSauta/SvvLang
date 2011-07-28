<ListMapIteratorElement> <ListMapNode> [Retain] node <MapIterator> [Retain] iterator <Logic> nextExists <Logic> prevExists

ListMapIteratorElement <ListMapNode> AdvancingValue (++) <ListMapIteratorElement> prevElement
	self.iterator ++
	self.nextExists = self.iterator NotNextEnd
	if prevElement != nil
		self.nextExists = self.nextExists Or prevElement.nextExists
	self.prevExists = yes
	return self.iterator ThisData

ListMapIteratorElement <ListMapNode> ReturningValue (++) <ListMapIteratorElement> prevElement
	self.iterator --
	self.nextExists = yes
	self.prevExists = self.iterator NotPrevBegin
	if prevElement != nil
		self.prevExists = self.prevExists Or prevElement.prevExists
	return self.iterator ThisData

ListMapIteratorElement Clone
	toReturn = <ListMapIteratorElement>
	toReturn.node = self.node
	toReturn.iterator = self.iterator Clone
	toReturn.nextExists = self.nextExists
	toReturn.prevExists = self.prevExists
	return toReturn

ListMapIteratorElement DeepClone
	toReturn = <ListMapIteratorElement>
	toReturn.node = self.node
	toReturn.iterator = self.iterator DeepClone
	toReturn.nextExists = self.nextExists
	toReturn.prevExists = self.prevExists
	return toReturn

ListMapIteratorElement <Comparison> Compare <ListMapIteratorElement> element
	candidate = self.node ? element.node
	if candidate == equal
		candidate = self.iterator ? element.iterator
	return candidate

ListMapIteratorElement Destroy
	self.node Release
	self.iterator Release
	return self Destroy

