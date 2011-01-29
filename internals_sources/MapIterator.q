<MapIterator> <Map> [Retain] map <ListIterator> [Retain] keysIterator <ListIterator> [Retain] valuesIterator

MapIterator SetMap <Map> map
	self.map = map
	return self

MapIterator ToBegin
	self.keysIterator = self.map.keys First
	self.valuesIterator = self.map.values First
	return self

MapIterator ToEnd
	self.keysIterator = self.map.keys Last
	self.valuesIterator = self.map.values Last
	return self

MapIterator Next (++)
	self.keysIterator ++
	self.valuesIterator ++
	return self

MapIterator Prev (--)
	self.keysIterator --
	self.valuesIterator --
	return self

MapIterator <Logic> ThisEnd
	return self.keysIterator ThisEnd

MapIterator <Logic> ThisBegin
	return self.keysIterator ThisBegin

MapIterator <Logic> PrevBegin
	return self.keysIterator PrevBegin

MapIterator <Logic> NextEnd
	return self.keysIterator NextEnd

MapIterator <Object> ThisKey
	return self.keysIterator ThisData

MapIterator <Object> NextKey
	return self.keysIterator NextData

MapIterator <Object> PrevKey
	return self.keysIterator PrevData

MapIterator <Object> ThisValue (ThisData Data)
	return self.valuesIterator ThisData

MapIterator <Object> NextValue
	return self.valuesIterator NextData

MapIterator <Object> PrevValue
	return self.valuesIterator PrevData

MapIterator <Comparation> Compare <MapIterator> mapIterator
	candidate = self.keysIterator ? mapIterator.keysIterator
	if candidate == equal
		candidate = self.valuesIterator ? mapIterator.valuesIterator
	return candidate

MapIterator Clone
	toReturn = <MapIterator>
	toReturn.map = self.map
	toReturn.keysIterator = self.keysIterator Clone
	toReturn.valuesIterator = self.valuesIterator Clone
	return toReturn

MapIterator DeepClone
	toReturn = <MapIterator>
	toReturn.map = self.map
	toReturn.keysIterator = self.keysIterator DeepClone
	toReturn.valuesIterator = self.valuesIterator DeepClone
	return toReturn

MapIterator Destroy
	self.keysIterator Release
	self.valuesIterator Release
	self.map Release
	return self Destroy
