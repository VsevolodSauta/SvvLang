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
	uid = self.machine ImportUID "SvvLanguage_C/externals/Объект" 
	object = self.machine ObjectByUID uid
	
	object ObjectSetBasicMethod self &ExternalObjectManipulator_CloneUIDObjectBasicMethod "Клонирование Тип=ЗапросЗапрос=Клонировать"
	object ObjectSetBasicMethod self &ExternalObjectManipulator_DoUIDObjectBasicMethod "Специализация Тип=ЗапросЗапрос=Выполнить_Тело"
	self.objectMasterCopy = (self.machine UIDToObject uid) DeepClone
	autoreleasePool --
	return uid

ExternalObjectManipulator <List> CloneUIDObjectInternalRoutine <List> uid
	object = self.machine UIDToObject uid
	uidToReturn = self.machine GenerateUID
	objectToReturn = self.objectMasterCopy DeepClone
	objectToReturn ObjectResetMethodsDestructive ((object ObjectMethods) TempDeepClone)
	objectToReturn ObjectResetFieldsDestructive ((object ObjectFields) TempDeepClone)
	objectToReturn ObjectResetJobsDestructive ((object ObjectJobs) TempDeepClone)
	objectToReturn ObjectRemoveAllIdentifiers
	self.machine SetUIDToObject uidToReturn objectToReturn
	objectToReturn Release
	return uidToReturn

ExternalObjectManipulator DoUIDObjectBasicMethod <Processor> processor
	tempMethodName = "Специализация, временный метод"
	object = self.machine UIDToObject processor.contextUID
	job = processor ContextJob
	methodBody = processor EntityFromMessageField "Тело" "Специализация Тип=ЗапросЗапрос=Выполнить_Тело"
	job JobSetMethodBody methodBody tempMethodName
	processor InvokeMethodWithParameters tempMethodName (entitiesFactory CreateEmptyListMap)
	(object ObjectMethods) Remove tempMethodName
	replyMessage = entitiesFactory CreateEmptyMessage
	replyMessage MessageSetAnswerSuccess
	processor SendReplyForMessage replyMessage "Специализация Тип=ЗапросЗапрос=Выполнить_Тело"
	return self

ExternalObjectManipulator CloneUIDObjectBasicMethod <Processor> processor
	uidToReturn = self CloneUIDObjectInternalRoutine processor.contextUID
	replyMessage = entitiesFactory CreateEmptyMessage
	replyMessage MessageSetAnswerSuccess
	replyMessage AtPut "Клон" uidToReturn
	processor SendReplyForMessage replyMessage "Клонирование Тип=ЗапросЗапрос=Клонировать"
	return self

