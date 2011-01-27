<UIDGenerator> <Number> [Clone] currentUID

UIDGenerator Init
	DEBUG_PUSH ("UID Generator: Initing.")
	self.currentUID = 0
	DEBUG_POP ("UID Generator: Inited.")
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

UIDGenerator <List> GetUID
	DEBUG_PUSH ("UID Generator: Generating UID.")
	def stringFactory FromNumber self.currentUID
	self.currentUID ++
	DEBUG_POP ("UID Generator: UID generated.")

