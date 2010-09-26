<ListNode> <ListNode> next <ListNode> prev data

ListNode Clone
	toReturn = <ListNode>
	toReturn.next = self.next
	toReturn.prev = self.prev
	toReturn.data = self.data
	toReturn.data Retain
	return toReturn

ListNode <Comparation> Compare listNode
	return (self Hash) Compare (listNode Hash)

ListNode <Object> Destroy
	self.data Release
	return (self AsObject) Destroy

