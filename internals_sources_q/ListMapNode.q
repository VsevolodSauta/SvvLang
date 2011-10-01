<ListMapNode@Object> <Map> [Retain] nextMap <Logic> mapped [Retain] mapping

ListMapNode Init
	self.nextMap = <Map>
	self.mapping = nil
	self.mapped = false
	return self

ListMapNode Destroy
	self.nextMap Release
	self.mapping Release
	return super Destroy

ListMapNode Clone
	toReturn = <ListMapNode>
	toReturn.nextMap = self.nextMap Clone
	toReturn.mapping = self.mapping
	toReturn.mapped = self.mapped
	return toReturn

ListMapNode DeepClone
	toReturn = <ListMapNode>
	toReturn.nextMap = self.nextMap DeepClone
	toReturn.mapping = (self.mapping DynamicallyDeepClone) Autorelease
	toReturn.mapped = self.mapped
	return toReturn

ListMapNode CompareSameGID <ListMapNode> listMapNode
	candidate = self.mapped ? listMapNode.mapped
	if candidate != equal
		return candidate
	if self.mapped
		candidate = self.mapping ? listMapNode.mapping
		if candidate != equal
			return candidate
	return self.nextMap ? listMapNode.nextMap

ListMapNode MergeRecursiveStrong <ListMapNode> listMapNode
	if listMapNode.mapped
		self.mapped = true
		self.mapping = listMapNode.mapping
	keysIterator = listMapNode.nextMap.keys First
	while keysIterator NotThisEnd
		key = keysIterator CharData
		value = self.nextMap At key
		if value == nil
			value = <ListMapNode>
			self.nextMap AtPut key value
			value Release
		value MergeRecursiveStrong (listMapNode.nextMap At key)
	return self
