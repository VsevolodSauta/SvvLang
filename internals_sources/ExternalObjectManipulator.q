<ExternalObjectManipulator> <Machine> machine <ListMap> objectMasterCopy

ExternalObjectManipulator Init
	return self

ExternalObjectManipulator Clone
	return self Retain

ExternalObjectManipulator DeepClone
	return self Retain

ExternalObjectManipulator Destroy
	self.objectMasterCopy Release
	return self Destroy

ExternalObjectManipulator Compare <ExternalObjectManipulator> manipulator
	return equal

ExternalObjectManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalObjectManipulator <List> CreateUIDObject
	autoreleasePool ++
	uid = self.machine ImportUID "Объект" 
	object = self.machine ObjectByUID uid
	object ObjectSetBasicMethod self &ExternalObjectManipulator_CloneUIDObjectBasicMethod "Клонирование Тип=ЗапросЗапрос=Клонировать" 
	self.objectMasterCopy = (self.machine UIDToObject uid) DeepClone
	autoreleasePool --
	return uid

ExternalObjectManipulator CloneUIDObjectInternalRoutine <List> uid
	object = self.machine UIDToObject uid
	uidToReturn = self.machine GenerateUID
	objectToReturn = self.objectMasterCopy DeepClone
	objectToReturn ObjectResetMethodsDestructive ((object ObjectMethods) TempDeepClone)
	objectToReturn ObjectResetFieldsDestructive ((object ObjectFields) TempDeepClone)
	objectToReturn ObjectRemoveAllIdentifiers
	self.machine SetUIDToObject uidToReturn objectToReturn
	objectToReturn Release
	return uidToReturn


ExternalObjectManipulator CloneUIDObjectBasicMethod <Processor> processor
	uidToReturn = self CloneUIDObjectInternalRoutine processor.contextUID
	replyMessage = entitiesFactory CreateEmptyListMap
	replyMessage AtPut "Ответ" "Успех"
	replyMessage AtPut "Клон" uidToReturn
	processor SendReplyForMessage replyMessage "Клонировать "
	return self

