<Actor> <ListMap> slotEntities <ListMap> slotTypes

Actor Init
	slotEntities = <ListMap>
	slotTypes = <ListMap>
	return self

Actor HasSlot slotName
	return slotEntities Contains slot

Actor GetSlot slotName
	slotType = slotTypes At slotName
	if slotType == ("Method")
		
	

Actor Run
	console PrintString ("Actor is running.")
	return self

Actor Destroy
	return self Destroy

Actor Clone
	return self

Actor <Comparation> Compare <Actor> actor
	return equal

