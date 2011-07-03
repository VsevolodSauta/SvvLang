<ExternalActorManipulator> <Machine> machine <ListMap> actorMasterCopy

ExternalActorManipulator Init
	return self

ExternalActorManipulator Clone
	return self Retain

ExternalActorManipulator DeepClone
	return self Retain

ExternalActorManipulator Destroy
	self.actorMasterCopy Release
	return self Destroy

ExternalActorManipulator Compare <ExternalActorManipulator> manipulator
	return equal

ExternalActorManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalActorManipulator <List> CreateUIDActor
	(threadManager AutoreleasePool) ++
	actor = entitiesFactory CreateEmptyActor

	job = entitiesFactory CreateEmptyJob
	self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Клонироваться" self &ExternalActorManipulator_CloneUIDActorBasicMethod job
	actor ActorSetJob job "Основная работа актора"

	job = entitiesFactory CreateEmptyJob
	self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Выполнить" self &ExternalActorManipulator_DoUIDActorBasicMethod job
	actor ActorSetJob job "Специализация"

	self.actorMasterCopy = actor DeepClone

	uid = self.machine GenerateUID
	self.machine SetUIDToActor uid actor

	(threadManager AutoreleasePool) --
	return uid

ExternalActorManipulator <List> CloneUIDActorInternalRoutine <List> uid
	actor = self.machine UIDToActor uid
	uidToReturn = self.machine GenerateUID
	actorToReturn = self.actorMasterCopy DeepClone
	actorToReturn ActorResetMethodsDestructive ((actor ActorMethods) TempDeepClone)
	actorToReturn ActorResetFieldsDestructive ((actor ActorFields) TempDeepClone)
	actorToReturn ActorResetJobsDestructive ((actor ActorJobs) TempDeepClone)
	actorToReturn ActorRemoveAllIdentifiers
	self.machine SetUIDToActor uidToReturn actorToReturn
	actorToReturn Release
	return uidToReturn

ExternalActorManipulator DoUIDActorBasicMethod <Processor> processor
	tempMethodName = "Специализация, временный метод"
	actor = processor ContextActor
	job = processor ContextJob
	methodBody = processor EntityFromMessageField "Тело" "Специализация Тип=ЗапросЗапрос=Выполнить_Тело"
	job JobSetMethodBody methodBody tempMethodName
	processor InvokeMethodWithParameters tempMethodName (entitiesFactory CreateEmptyListMap)
	(actor ActorMethods) Remove tempMethodName
	replyMessage = entitiesFactory CreateEmptyMessage
	replyMessage MessageSetAnswerSuccess
	processor SendReplyForMessage replyMessage "Специализация Тип=ЗапросЗапрос=Выполнить_Тело"
	return self

ExternalActorManipulator CloneUIDActorBasicMethod <Processor> processor
	uidToReturn = self CloneUIDActorInternalRoutine (processor ContextActorUID)
	replyMessage = entitiesFactory CreateEmptyMessage
	replyMessage MessageSetAnswerSuccess
	replyMessage AtPut "Клон" uidToReturn
	processor SendReplyForMessage replyMessage "Клонирование Тип=ЗапросЗапрос=Клонировать"
	return self
