<ListNode> <ListNode> next <ListNode> prev data

ListNode Clone
	toReturn = <ListNode>
	toReturn.next = self.next
	toReturn.prev = self.prev
	toReturn.data = self.data
	toReturn.data Retain
	return toReturn

ListNode <Comparation> Compare <ListNode> listNode
	candidate = self.data Compare listNode.data
	if candidate != equal
		return candidate
	if (self.next Hash) == (listNode.next Hash)
		return (self.prev Hash) Compare (listNode.prev Hash)
	return (self.next Hash) Compare (listNode.next Hash)

ListNode <Object> Destroy
	self.data Release
	return (self AsObject) Destroy

