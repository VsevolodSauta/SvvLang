<UIDGenerator> <Number> [Clone] currentUID

UIDGenerator Init
	self.currentUID = 0
	return self

UIDGenerator Clone
	toReturn = <UIDGenerator>
	toReturn.currentUID = self.currentUID
	return toReturn

UIDGenerator DeepClone
	toReturn = <UIDGenerator>
	toReturn.currentUID = self.currentUID
	return toReturn

UIDGenerator Destroy
	self.currentUID Release
	return self Destroy

UIDGenerator <Comparation> Compare uidGenerator
	return (self Hash) ? (uidGenerator Hash)

UIDGenerator <List> GenerateUID (GetUID)
	def (("<" + (stringFactory FromNumber self.currentUID)) + ">")
	self.currentUID ++

