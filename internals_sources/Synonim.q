<Synonim> <List> [Retain] object <List> references

Synonim Init
	references = <List>
	return self

Synonim SetObject (SetField) <List> object
	self.object = object
	return self

Synonim Unite (Intersect) <Synonim> synonim
	iterator = self.references First
	while iterator NotThisEnd
		synonim AddReference (iterator ListMapData)
		iterator Remove
		self Release
		iterator ++
	return nil
	

Synonim AddReference <ListMap> location
	self.references PushSorted location
	(location ListMapAt ("Пространство имен")) AtPut (location ListAt ("Имя поля")) self
	self Retain
	return self

Synonim RemoveReference <ListMap> location
	if self.references RemoveFirstWithConfirmation location
		(location ListMapAt ("Пространство имен")) Remove (location ListAt ("Имя поля"))
		self Release
	return self

Synonim RemoveNamespace <ListMap> namespace
	iterator = self.references First
	while iterator NotThisEnd
		if ((iterator ListMapData) At ("Пространство имен")) == namespace
			iterator Remove
			self Release
		else
			iterator ++
	return self

Synonim Destroy
	self.object Release
	self.references Release
	return self Destroy

Synonim Clone
	return self

Synonim <Comparation> Compare <Synonim> synonim
	return self.object ? synonim.object
