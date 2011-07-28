<Synonim> <List> [Retain] uid <List> references

Synonim Init
	self.references = <List>
	// self Autorelease
	return self

Synonim SetUID <List> uid
	self.uid = uid
	return self

Synonim <List> GetUID (UID)
	return self.uid

Synonim Unite (Intersect) <Synonim> synonim
	iterator = synonim.references First
	while iterator NotThisEnd
		reference = (iterator ListMapData) Retain
		iterator Remove
		self AddReference (reference)
		reference Release
	return self

Synonim AddToNamespaceWithName <ListMap> namespace <List> name
	reference = <ListMap>
	reference AtPut ("Пространство имен") namespace
	reference AtPut ("Имя поля") name
	self.references PushSorted reference
	reference Release
	namespace AtPut name self
	return self

Synonim AddReference <ListMap> location
	self.references PushSorted location
	(location ListMapAt ("Пространство имен")) AtPut (location ListAt ("Имя поля")) self
	return self

Synonim RemoveReference <ListMap> location
	if self.references RemoveFirstWithConfirmation location
		(location ListMapAt ("Пространство имен")) Remove (location ListAt ("Имя поля"))
	return self

Synonim RemoveNamespace <ListMap> namespace
	iterator = self.references First
	while iterator NotThisEnd
		if ((iterator ListMapData) At ("Пространство имен")) == namespace
			iterator Remove
		else
			iterator ++
	return self

Synonim Destroy
	self.uid Release
	self.references Release
	return self Destroy

Synonim Clone
	toReturn = <Synonim>
	toReturn.uid = self.uid
	return self

Synonim DeepClone
	toReturn = <Synonim>
	toReturn.uid = self.uid
	return self

Synonim <Comparison> Compare <Synonim> synonim
	return self.uid ? synonim.uid
