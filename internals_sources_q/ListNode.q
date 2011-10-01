<ListNode@Object> <ListNode> next <ListNode> prev [Retain] data

ListNode Init
	return self

ListNode Clone
	toReturn = <ListNode>
	toReturn.next = self.next
	toReturn.prev = self.prev
	toReturn.data = self.data
	return toReturn

ListNode DeepClone
	toReturn = <ListNode>
	toReturn.next = self.next
	toReturn.prev = self.prev
	toReturn.data = self.data DynamicallyDeepClone
	return toReturn

ListNode <Comparison> CompareSameGID <ListNode> listNode
	candidate = self.data ? listNode.data
	if candidate != equal
		return candidate
	if (self.next Hash) == (listNode.next Hash)
		return (self.prev Hash) ? (listNode.prev Hash)
	return (self.next Hash) ? (listNode.next Hash)

ListNode Destroy
	self.data Release
	return super Destroy
