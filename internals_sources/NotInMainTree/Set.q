<Set> <List> list <Number> capacity

Set Init
	self.list = <List>
	self.capacity = 0
	return self

Set Compare <Set> set
	return (self.list) Compare (set.list)

Set Destroy
	self.list Destroy
	self.capacity Destroy
	return (self AsObject) Destroy

Set Clone
	toReturn = <Set>
	toReturn.list Concatenate self.list
	toReturn.capacity = self.capacity Clone
	return toReturn

Set Add object
	if self.list NotCheckAndInsert object
		self.capacity Inc
	return self

Set Remove object
	iterator = self.list Search object
	if iterator NotThisEnd
		iterator ThisRemove
		self.capacity Dec
	return self
