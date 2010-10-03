<ListNode> <ListNode> next <ListNode> prev [Retain] data

ListNode Clone
	toReturn = <ListNode>
	toReturn.next = self.next
	toReturn.prev = self.prev
	toReturn.data = self.data
	return toReturn

ListNode <Comparation> Compare <ListNode> listNode
	candidate = self.data ? listNode.data
	if candidate != equal
		return candidate
	if (self.next Hash) == (listNode.next Hash)
		return (self.prev Hash) ? (listNode.prev Hash)
	return (self.next Hash) ? (listNode.next Hash)

ListNode <Object> Destroy
	self.data Release
	return (self AsObject) Destroy

