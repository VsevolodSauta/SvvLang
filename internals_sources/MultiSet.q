<MultiSet> <List> [Retain] list

MultiSet Init
	self.list = <List>
	return self

MultiSet <Object> Destroy
	self.list Release
	return (self.list AsObject) Destroy

MultiSet Clone
	toReturn = <MultiSet>
	toReturn.list = self.list Clone
	return toReturn

MultiSet <Comparation> Compare <MultiSet> multiset
	return self.list Compare multiset.list

MultiSet Push (Add +) object
	self.list PushSorted object
	return self

MultiSet <Logic> Contains (Has) object
	return self.list Contains object

MultiSet RemoveOnce (Remove - \) object
	self.list RemoveFirst object
	return self

MultiSet RemoveEvery (-- \\) object
	self.list RemoveEvery object
	return self

