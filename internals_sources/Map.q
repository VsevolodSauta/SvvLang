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
	keysIterator = self.keys First
	valuesIterator = self.values First
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			valuesIterator SetThisData value
			return self
	keysIterator AddBefore key
	valuesIterator AddBefore value
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

Map ContainsKey (HasKey) key
	keysIterator = self.keys First
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			return true
	return false

Map GetValueForKey (GetAt AtGet) key
	keysIterator = self.keys First
	valuesIterator = self.values First
	while keysIterator NotThisEnd
		if (keysIterator ThisData) < key
			keysIterator ++
			valuesIterator ++
		elif (keysIterator ThisData) > key
			break
		else
			return valuesIterator ThisData
	return nil

