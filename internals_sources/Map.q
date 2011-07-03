<Map> <List> [Retain] keys <List> [Retain] values

Map Init
	self.keys = <List>
	self.values = <List>
	return self

Map Destroy
	self.keys Release
	self.values Release
	return self Destroy

Map Clone
	toReturn = <Map>
	toReturn.keys = self.keys Clone
	toReturn.values = self.values Clone
	return toReturn

Map DeepClone
	toReturn = <Map>
	toReturn.keys = self.keys DeepClone
	toReturn.values = self.values DeepClone
	return toReturn

Map <Comparation> Compare <Map> map
	candidate = self.keys ? map.keys
	if candidate != equal
		return candidate
	return self.values ? map.values

Map <Logic> Empty
	return self.keys Empty

Map <Number> Size
	return self.keys Size

Map Add (AtPut PutAt +) key value
	keysIterator = self.keys SystemFirst
	valuesIterator = self.values SystemFirst
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			valuesIterator SetThisData value
			keysIterator Release
			valuesIterator Release
			return self
	keysIterator AddBefore key
	valuesIterator AddBefore value
	keysIterator Release
	valuesIterator Release
	return self

Map RemoveKey (Remove Delete DeleteKey - \) key
	keysIterator = self.keys First
	valuesIterator = self.values First
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			valuesIterator ThisRemove
			keysIterator ThisRemove
			break
	return self

Map RemoveKeyConfirming (RemoveConfirming -? \?) key
	keysIterator = self.keys First
	valuesIterator = self.values First
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			valuesIterator ThisRemove
			keysIterator ThisRemove
			return true
	return false

Map ContainsKey (HasKey Contains) key
	keysIterator = self.keys SystemFirst
	toReturn = false
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
		else
			if (keysIterator ThisData) == key
				toReturn = true
			break
	keysIterator Release
	return toReturn

Map GetValueForKey (GetAt AtGet At) key
	keysIterator = self.keys SystemFirst
	valuesIterator = self.values SystemFirst
	toReturn = nil
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		else
			if (keysIterator ThisData) == key
				toReturn = valuesIterator ThisData
			break
	keysIterator Release
	valuesIterator Release
	return toReturn

Map <MapIterator> First
	iterator = <MapIterator>
	iterator SetMap self
	iterator ToBegin
	return iterator Autorelease

Map <MapIterator> Last
	iterator = <MapIterator>
	iterator SetMap self
	iterator ToEnd
	return iterator Autorelease
