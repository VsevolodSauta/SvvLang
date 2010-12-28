<MultiSet> <List> [Retain] list

MultiSet Init
	DEBUG_PUSH ("Multiset: Initing.")
	self.list = <List>
	DEBUG_POP ("Multiset: Inited.")
	return self

MultiSet <Object> Destroy
	DEBUG_PUSH ("Multiset: Destroying.")
	self.list Release
	DEBUG_POP ("Multiset: Destroyed.")
	return (self AsObject) Destroy

MultiSet Clone
	toReturn = <MultiSet>
	toReturn.list = self.list Clone
	return toReturn

MultiSet <Comparation> Compare <MultiSet> multiset
	return self.list Compare multiset.list

MultiSet Push (Add +) object
	DEBUG_PUSH ("Multiset: Pushing.")
	self.list PushSorted object
	DEBUG_POP ("Multiset: Pushed.")
	return self

MultiSet <Logic> Contains (Has) object
	return self.list Contains object

MultiSet RemoveOnce (Remove - \) object
	self.list RemoveFirst object
	return self

MultiSet RemoveEvery (-- \\) object
	self.list RemoveEvery object
	return self

MultiSet <Logic> Empty
	return self.list Empty

