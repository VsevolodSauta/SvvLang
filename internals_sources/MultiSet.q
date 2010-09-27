<MultiSet> <List> list

MultiSet Init
	self.list = <List>
	return self

MultiSet <Object> Destroy
	self.list Release
	return (self.list AsObject) Destroy

MultiSet Clone
	toReturn = <MultiSet>
	toReturn.list Release
	toReturn.list = self.list Clone
	return toReturn

MultiSet Compare <MultiSet> multiset
	return ((self.list TempClone) Sort) Compare ((multiset.list TempClone) Sort)

MultiSet Push object
	self.list PushBack object
	return self

MultiSet <Logic> Contains object
	return self.list Contains object

MultiSet RemoveOnce object
	self.list RemoveFirst object
	return self

MultiSet RemoveEvery object
	self.list RemoveEvery object
	return self

