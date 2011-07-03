<Processor> <List> [Retain] contextActorUID <List> [Retain] contextJobName <ListMap> [Retain] contextJobStageName <Machine> machine <Stack> localNamespaces  <ProcessorCommandSystem> commandSystem <ListMap> [Retain] contextMessages <ListMap> processorCodes

Processor <Processor> Clone
	return <Processor>

Processor <Processor> DeepClone
	return <Processor>

Processor Destroy
	self.contextActorUID Release
	self.contextJobName Release
	self.contextJobStageName Release
	self.localNamespaces Release
	self.commandSystem Release
	return self Destroy

Processor <Comparation> Compare <Processor> processor
	return equal


Processor SetMachine <Machine> machine
	self.machine = machine
	return self

Processor <List> ContextActorUID
	return self.contextActorUID

Processor <List> ContextJobName
	return self.contextJobName

Processor <List> ContextJobStageName
	return self.contextJobStageName

Processor <ListMap> ContextActor
	return self.machine UIDToActor self.contextActorUID

Processor <ListMap> ContextJob
	return (self ContextActor) ActorJob self.contextJobName

Processor <ListMap> ContextJobStage
	return (self ContextJob) JobStage self.contextJobStageName

Processor Init
	self.localNamespaces = <Stack>
	self.commandSystem = <ProcessorCommandSystem>
	self.commandSystem SetProcessor self
	return self


// ============================================
// Управление методами

Processor DefineActorMethod <ListMap> method <List> methodName
	(self ContextActor) ActorSetMethod method methodName
	return self

Processor DefineActorMethodWithBody <List> methodBody <List> methodName
	(self ContextActor) ActorSetMethod (entitiesFactory CreateMethodWithBody methodBody) methodName
	return self

Processor UnDefineMethod <List> methodName
	if ((self ContextJob) JobMethods) ContainsKey methodName
		(self ContextJob) JobRemoveMethod methodName
	else
		(self ContextActor) ActorRemoveMethod methodName
	return self

Processor UnDefineActorMethod <List> methodName
	(self ContextActor) ActorRemoveMethod methodName
	return self

Processor DefineJobMethod <ListMap> method <List> methodName
	(self ContextJob) JobSetMethod method methodName
	return self

Processor DefineJobMethodWithBody <List> methodBody <List> methodName
	(self ContextJob) JobSetMethod (entitiesFactory CreateMethodWithBody methodBody) methodName
	return self

Processor UnDefineJobMethod <List> methodName
	(self ContextJob) JobRemoveMethod methodName
	return self

// ============================================
// Управление полями



Processor DefineFieldInNameSpaceWithUID <List> fieldName <ListMap> nameSpace <List> uid
	synonim = <Synonim>
	synonim SetUID uid
	reference = <ListMap>
	reference AtPut ("Пространство имен") nameSpace
	reference AtPut ("Имя поля") fieldName
	synonim AddReference reference
	reference Release

	// Уже выполнено при инициализации синонима
	synonim Release
	return self

Processor SetField <List> fieldName <List> uid
	(self FieldNameToSynonim fieldName) SetUID uid
	return self

Processor UniteField <List> destinationFieldName <List> sourceFieldName
	(self FieldNameToSynonim destinationFieldName) Unite (self FieldNameToSynonim sourceFieldName)
	return self

Processor UnDefineFieldInNamespace <List> fieldName <List> locationType
	if locationType == nil
		locationType = self FieldNameToNamespaceName fieldName
	place = <ListMap>
	place AtPut ("Имя") fieldName
	place AtPut ("Пространство имен") (self NamespaceNameToNamespace locationType)
	synonim = self FieldNameToSynonim fieldName
	synonim RemoveReference place
	place Release
	return self


// ============================================
// Управление работами

Processor AddJobWithName <ListMap> job <List> jobName
	(self ContextActor) ActorSetJob job jobName
	return self

Processor FinishThisJob
	((self ContextActor) ActorRemoveJob (self.contextJobName)
	return self


// ============================================
// Управление стадиями

Processor AddJobStage <List> jobStage <List> jobStageName
	self AddJobStageInJob jobStage jobStageName self.contextJobName
	return self

Processor BlockStage <List> stageName
	self BlockStageInJob stageName self.contextJobName
	return self

Processor UnBlockStage <List> stageName
	self UnBlockStageInJob stageName self.contextJobName
	return self

Processor RemoveJobStage <List> jobStageName
	self RemoveJobStageInJob jobStageName self.contextJobName
	return self

Processor RemoveAllStages
	self RemoveAllStagesInJob self.contextJobName
	return self


// ============================================
// Управление ожидаемыми сообщениями

Processor AddMessageSlot <List> messageSlot <List> messageSlotName
	self AddMessageSlotInJob messageSlot messageSlotName self.contextJobName
	return self

Processor BlockMessageSlot <List> messageSlotName
	self BlockMessageSlotInJob messageSlotName self.contextJobName
	return self

Processor UnBlockMessageSlot <List> messageSlotName
	self UnBlockMessageSlotInJob messageSlotName self.contextJobName
	return self

Processor RemoveMessageSlot <List> messageSlotName
	self RemoveMessageSlotInJob messageSlotName self.contextJobName
	return self

Processor RemoveAllMessageSlots
	self RemoveAllMessageSlotsInJob self.contextJobName
	return self


// ============================================
// Управление стадиями и ожидаемыми сообщениями

Processor AttachToStageMessageSlot <List> stageName <List> messageName
	self AttachToStageMessageSlotInJob stageName messageName self.contextJobName
	return self

Processor RemoveAllStagesAndMessageSlots
	self RemoveAllStagesAndMessageSlotsInJob self.contextJobName
	return self


// ============================================
// Управление полученными сообщениями

Processor RemoveMessageInMessageSlot <List> messageSlotName
	self RemoveMessageInMessageSlotInJob messageSlotName self.contextJobName
	return self

Processor RemoveAllMessagesOfCurrentStageForCurrentStage
	self RemoveAllMessagesOfCurrentStageForAllStagesInJob self.contextJobName
	return self

Processor RemoveAllMessagesOfCurrentStageForAllStages
	self RemoveAllMessagesOfCurrentStageForAllStagesInJob self.contextJobName
	return self

Processor RemoveAllMessagesOfAllOpenedStages
	self RemoveAllMessagesOfAllOpenedStagesInJob self.contextJobName
	return self

Processor RemoveAllReceivedMessages
	self RemoveAllReceivedMessagesInJob self.contextJobName
	return self


// ============================================
// Управление стадиями в произвольной работе

Processor AddJobStageInJob <List> jobStage <List> jobStageName <List> jobName
	((self ContextActor) ActorJob jobName) JobSetStage jobStage jobStageName
	return self

Processor BlockStageInJob <List> stageName <List> jobName
	(((self ContextActor) ActorJob jobName) JobStage stageName) StageSetBlocked
	return self

Processor UnBlockStageInJob <List> stageName <List> jobName
	stage = (((self ContextActor) ActorJob jobName) JobStage stageName)
	if (stage StageMessagesCounter) == 0
		stage StageSetReady
	else
		stage StageSetWaiting
	return self

Processor RemoveJobStageInJob <List> jobStageName <List> jobName
	iterator = ((self ContextActor) ActorJob jobName) JobMessageSlotsIterator
	while iterator NotThisEnd
		messageSlot = (iterator Data) AsListMap
		stages = messageSlot MessageSlotStages
		stages RemoveFirst jobStageName
		iterator ++
	((self ContextActor) ActorJob jobName) JobRemoveStage jobStageName
	return self

Processor RemoveAllStagesInJob <List> jobName
	((self ContextActor) ActorJob jobName) JobRemoveAllStages
	messageSlotsIterator = ((self ContextActor) ActorJob jobName) JobMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		(messageSlot MessageSlotStages) RemoveAll
		messageSlotsIterator ++
	return self


// ============================================
// Управление ожидаемыми сообщениями в произвольной работе

Processor AddMessageSlotInJob <List> messageSlot <List> messageSlotName <List> jobName
	((self ContextActor) ActorJob jobName) JobSetMessageSlot messageSlot messageSlotName
	return self

Processor BlockMessageSlotInJob <List> messageSlotName <List> jobName
	(((self ContextActor) ActorJob jobName) JobMessageSlot messageSlotName) MessageSlotBlock
	return self

Processor UnBlockMessageSlotInJob <List> messageSlotName <List> jobName
	(((self ContextActor) ActorJob jobName) JobMessageSlot messageSlotName) MessageSlotOpen
	return self

Processor RemoveMessageSlotInJob <List> messageSlotName <List> jobName
	if (((self ContextActor) ActorJob jobName) JobMessageInMessageSlot messageSlotName) != nil
		stagesIterator = ((self ContextActor) ActorJob jobName) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			if (stage StageMessageSlots) RemoveFirstWithConfirmation messageSlotName
				stage StageDecrementMessagesCounter
				if (stage StageIsWaiting) And ((stage StageMessagesCounter) == 0)
					stage StageSetReady
			stagesIterator ++
	else
		stagesIterator = ((self ContextActor) ActorJob jobName) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			(stage StageMessageSlots) RemoveFirst messageSlotName
			stagesIterator ++
	((self ContextActor) ActorJob jobName) JobRemoveMessageSlot messageSlotName
	return self

Processor RemoveAllMessageSlotsInJob <List> jobName
	((self ContextActor) ActorJob jobName) JobRemoveAllMessageSlots
	jobStagesIterator = ((self ContextActor) ActorJob jobName) JobStagesIterator
	while jobStagesIterator NotThisEnd
		jobStage = (jobStagesIterator Data) AsListMap
		(jobStage StageMessageSlots) RemoveAll
		(jobStage StageSetMessagesCounter 0)
		jobStage StageSetBlocked
		jobStagesIterator ++
	return self


// ============================================
// Управление стадиями и ожидаемыми сообщениями в произвольной работе

Processor AttachToStageMessageSlotInJob <List> stageName <List> messageName <List> jobName
	stage = ((self ContextActor) ActorJob jobName) JobStage stageName
	stagesInMessageSlot = (((self ContextActor) ActorJob jobName) JobMessageSlot messageName) MessageSlotStages
	if stagesInMessageSlot NotContains stageName
		messageSlotsInStage = stage StageMessageSlots
		stagesInMessageSlot Append stageName
		messageSlotsInStage Append messageName
		stage StageIncrementMessagesCounter
		if stage StageIsReady
			stage StageSetWaiting
	return self

Processor RemoveAllStagesAndMessageSlotsInJob <List> jobName
	((self ContextActor) ActorJob jobName) JobRemoveAllStages
	((self ContextActor) ActorJob jobName) JobRemoveAllMessageSlots
	return self


// ============================================
// Управление полученными сообщениями в произвольной работе

Processor RemoveMessageInMessageSlotInJob <List> messageSlotName <List> jobName
	messageSlot = ((self ContextActor) ActorJob jobName) JobMessageSlot messageSlotName
	if (messageSlot MessageSlotMessage) != nil
		messageSlot MessageSlotRemoveMessage nil
		if ((messageSlot MessageSlotMessages) Size) == 0
			stagesIterator = messageSlot MessageSlotStagesIterator
			while stagesIterator NotThisEnd
				stage = ((self ContextActor) ActorJob jobName) JobStage (stagesIterator ListData)
				stage StageIncrementMessagesCounter
				if stage StageIsReady
					stage StageSetWaiting
				stagesIterator ++
	return self

Processor RemoveAllMessagesOfCurrentStageForCurrentStageInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlotName = messageSlotsIterator ListData
		messageSlot = ((self ContextActor) ActorJob jobName) JobMessageSlot messageSlotName
		messageSlot MessageSlotRemoveMessage nil
		messageSlotsIterator ++
	return self

Processor RemoveAllMessagesOfCurrentStageForAllStagesInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlotName = messageSlotsIterator ListData
		messageSlot = ((self ContextActor) ActorJob jobName) JobMessageSlot messageSlotName
		message = messageSlot MessageSlotMessage
		messageMessageSlotsIterator = (message MessageAttributesMessageSlots) First
		while messageMessageSlotsIterator NotThisEnd
			messageMessageSlot = ((self ContextActor) ActorJob jobName) JobMessageSlot (messageMessageSlotsIterator ListData)
			messageMessageSlot MessageSlotRemoveMessage message
			messageMessageSlotsIterator ++
		messageSlotsIterator ++
	return self

Processor RemoveAllMessagesOfAllOpenedStagesInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlot = ((self ContextActor) ActorJob jobName) JobMessageSlot (messageSlotsIterator ListData)
		if messageSlot MessageSlotIsOpened
			messageSlot MessageSlotRemoveAllMessages
		messageSlotsIterator ++
	return self

Processor RemoveAllReceivedMessagesInJob <List> jobName
	messageSlotsIterator = ((self ContextActor) ActorJob jobName) JobMessageSlotsIterator
	stagesIterator = ((self ContextActor) ActorJob jobName) JobStagesIterator
	while stagesIterator NotThisEnd
		stage = stagesIterator ListMapData
		stage StageSetMessagesCounter ((stage StageMessageSlots) Size)
		stagesIterator ++
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		messageSlot MessageSlotRemoveAllMessages
		messageSlotsIterator ++
	return self


// ============================================
// Помошники для внутренней реализации

Processor <ListMap> CreateStageRequestEntityBasicMethodInJob <List> requestName entity <Method> basicMethod <ListMap> job
	messageSlot = entitiesFactory CreateRequestMessageSlot requestName
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity requestName requestName requestName messageSlot
	job JobSetBasicMethod entity basicMethod requestName
	return messageSlot

Processor <ListMap> CreateStageReplyEntityBasicMethodInJob <List> requestName entity <Method> basicMethod <ListMap> job
	messageSlot = entitiesFactory CreateReplyMessageSlot requestName
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity requestName requestName requestName messageSlot
	job JobSetBasicMethod entity basicMethod requestName
	return messageSlot

Processor <ListMap> CreateStageEmptyEntityBasicMethodInJob <List> requestName entity <Method> basicMethod <ListMap> job
	messageSlot = entitiesFactory CreateEmptyMessageSlot
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity requestName requestName requestName messageSlot
	job JobSetBasicMethod entity basicMethod requestName
	return messageSlot

Processor DefineFieldHelper <List> uid <List> fieldName <ListMap> nameSpace
	synonim = <Synonim>
	synonim SetUID uid
	reference = <ListMap>
	reference AtPut ("Пространство имен") nameSpace
	reference AtPut ("Имя поля") fieldName
	synonim AddReference reference
	reference Release
	synonim Release
	return self



// ============================================
// Всякая ерунда (не систематизировано)

Processor <Object> EntityFromNamedMessageField (EntityFromMessageField) <List> messageName <List> fieldName
	return (self MessageInMessageSlot messageName) ObjectAt fieldName


Processor <ListMap> NamespaceNameToNamespace <List> locationType
	if locationType == "Глобальное поле"
		return self.machine.globalContext
	elif locationType == "Поле объекта"
		return (self ContextActor) ActorFields
	elif locationType == "Поле работы"
		return (self ContextJob) JobFields
	elif locationType == "Локальное поле"
		return self.localNamespaces Peek
	else
		return nil


Processor <List> FieldNameToNamespaceName <List> fieldName
	if ((self.localNamespaces Peek) AsListMap) Contains fieldName
		return ("Локальное поле")
	elif ((self ContextJob) JobFields) Contains fieldName
		return ("Поле работы")
	elif ((self ContextActor) ActorFields) Contains fieldName
		return ("Поле объекта")
	elif (self.machine.globalContext) Contains fieldName
		return ("Глобальное поле")
	else
		return ("Нет такого поля")


Processor <Synonim> FieldNameToSynonim <List> fieldName
	candidate = ((self.localNamespaces Peek) AsListMap) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = ((self ContextJob) JobFields)  SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = ((self ContextActor) ActorFields) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate
	console PrintLnString ("!!!!!!!!! Ошибка! Взятие синонима отсутствующего поля.")
	return nil


Processor <List> FieldNameToUIDInJobActor <List> fieldName <ListMap> job <ListMap> actor
	candidate = (job JobFields) SynonimAt fieldName
	if candidate != nil
		return candidate UID
	candidate = (actor ActorFields) SynonimAt fieldName
	if candidate != nil
		return candidate UID

	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate UID

	parsedObject = jsonParser ParseValue (fieldName First)
	if parsedObject != jsonParser.error
		return (self.machine ActorsFactory) CreateActorFromObject parsedObject

	console PrintLnString ("!!!!!!!!! Ошибка! Взятие отсутствующего поля.")
	return nil


Processor <List> FieldNameToUID <List> fieldName
	if self.contextActorUID != nil
		return self FieldNameToUIDInJobActor fieldName (self ContextJob) (self ContextActor)

	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate UID

	parsedObject = jsonParser ParseValue (fieldName First)
	if parsedObject != jsonParser.error
		return (self.machine ActorsFactory) CreateActorFromObject parsedObject

	console PrintLnString ("!!!!!!!!! Ошибка! Взятие отсутствующего поля.")
	return nil



Processor <ListMap> MessageInMessageSlot <List> messageSlotName
	return self.contextMessages ListMapAt messageSlotName


Processor SendMessage <ListMap> message
	message MessageSetSender self.contextActorUID
	uid = message MessageReceiver
	receiver = self.machine ActorByUID uid
	self ProcessMessageForActor (message TempDeepClone) receiver
	self.machine ScheduleUID uid
	return self


Processor SendMessageToMessageField <ListMap> message <List> messageSlotName <List> fieldName
	receiver = ((self MessageInMessageSlot messageSlotName) At fieldName)
	message MessageSetReceiver receiver
	self SendMessage message
	return self


Processor SendReplyForMessage <ListMap> replyMessage <List> messageSlotName
	message = self MessageInMessageSlot messageSlotName
	receiver = message MessageSender
	request = message MessageRequest
	replyMessage = replyMessage TempDeepClone
	replyMessage MessageSetReceiver receiver
	replyMessage MessageSetRequest request
	replyMessage MessageSetTypeAnswer
	self SendMessage replyMessage
	return self


Processor InvokeMethodWithParameters <List> methodName <ListMap> parameters
	(threadManager AutoreleasePool) ++
	method = (self ContextJob) JobMethod methodName
	if method == nil
		method = (self ContextActor) ActorMethod methodName

	if method == nil
		console PrintLnString ("!!!!!!!! Ошибка! Вызов несуществующего метода.")
	else
		// SVV!
		console PrintString "Объект: "
		console PrintString self.contextActorUID
		console PrintString "  Процессор вызывает метод: "
		console PrintLnString methodName
		namespace = <ListMap>
		self.localNamespaces Push namespace
		namespace AddListMap parameters
		namespace Release
		if method LogicAt ("Базовый")
			basicMethod = method MethodAt ("Базовый метод")
			objectEntity = method ObjectAt ("Сущность")
			basicMethod Invoke objectEntity self
		else
			methodBody = method ListAt ("Тело")
			iterator = methodBody First
			while iterator NotThisEnd
				self.commandSystem Do (iterator ListMapData)
				iterator ++
		self.localNamespaces Pop
	(threadManager AutoreleasePool) --
	return self


Processor MessageConfirmsToParameterInJobActor <ListMap> message <ListMap> parameter <ListMap> job <ListMap> actor
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == "Совпадение"
		return (message At (parameter ListAt ("Ключ"))) == (parameter At ("Значение"))
	elif checkingMethod == "Совпадение с полем"
		uid = self FieldNameToUIDInJobActor (parameter At ("Значение")) job actor
		if uid Is nil
			return false
		return (message At (parameter ListAt ("Ключ"))) == uid
	elif checkingMethod == "Наличие"
		return (message ContainsKey (parameter ListAt ("Ключ")))
	return false


Processor <Logic> TryLinkMessageWithMessageSlotInJobActor <ListMap> message <ListMap> messageSlot <ListMap> job <ListMap> actor <List> messageSlotName <List> jobName
	confirms = true
	parametersIterator = (messageSlot ListAt ("Метод идентификации")) First
	while parametersIterator NotThisEnd
		parameter = parametersIterator ListMapData
		if self NotMessageConfirmsToParameterInJobActor message parameter job actor
			confirms = false
			break
		parametersIterator ++
	if confirms
		if ((messageSlot MessageSlotMessages) Size) > 0
			messageSlot MessageSlotSetMessage message
		else
			messageSlot MessageSlotSetMessage message
			message MessageSetJobNameAndMessageSlotName jobName messageSlotName
			waitingStageNamesIterator = (messageSlot MessageSlotStages) First
			while waitingStageNamesIterator NotThisEnd
				jobStage = (job JobStages) ListMapAt (waitingStageNamesIterator ListData)
				jobStage StageDecrementMessagesCounter
				if ((jobStage StageMessagesCounter) == 0) And (jobStage StageIsWaiting)
					jobStage StageSetReady
				waitingStageNamesIterator ++
	return confirms


Processor ProcessMessageForActor <ListMap> message <ListMap> actor
	assigned = false
	// console PrintLnString (message MessageRequest)
	jobsIterator = (actor ActorJobs) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		jobName = jobsIterator Key
		messageSlotsIterator = job JobMessageSlotsIterator
		while messageSlotsIterator NotThisEnd
			messageSlot = messageSlotsIterator ListMapData
			messageSlotName = messageSlotsIterator Key
			if messageSlot MessageSlotIsOpened
				assignedRightNow = self TryLinkMessageWithMessageSlotInJobActor message messageSlot job actor messageSlotName jobName
				assigned = assignedRightNow Or assigned
			messageSlotsIterator ++
		jobsIterator ++
	if assigned Not
		// Скорее всего эту ситуацию надо будет обрабатывать посылкой "неудачного" сообщения в ответ.
		// SVV!
		console PrintLnString "!!!!!!!!! Ошибка! Сообщение не обработано объектом."
	return self


// Что должно происходить при удалении сущности А из объекта на этапе выполнения метода?
// Наиболее правильное решение состоит в том, чтобы поддерживать множество удаленных сущностей
// и по завершению метода удалять эти сущности реально.


Processor ProcessOneJobIfAny
	jobsIterator = ((self ContextActor) ActorJobs) First
	while jobsIterator NotThisEnd
		job = (jobsIterator ListMapData)
		jobStagesIterator = job JobStagesIterator
		while jobStagesIterator NotThisEnd
			jobStage = jobStagesIterator ListMapData
			if jobStage StageIsReady
				self.contextMessages = <ListMap>
				self.contextJobStageName = jobStagesIterator Key
				self.contextJobName = jobsIterator Key
				messageSlotsIterator = jobStage StageMessageSlotsIterator
				while messageSlotsIterator NotThisEnd
					messageSlotName = messageSlotsIterator ListData
					message = (job JobMessageSlot messageSlotName) MessageSlotMessage
					self.contextMessages AtPut messageSlotName message
					self RemoveMessageInMessageSlot messageSlotName
					messageSlotsIterator ++
				emptyParameters = <ListMap>
				self InvokeMethodWithParameters (jobStage StageMethod) emptyParameters
				emptyParameters Release
				self.contextJobStageName = nil
				self.contextJobName = nil
				self.contextActorUID = nil
				self.machine ProcessorFinishedWork self
				return self
			jobStagesIterator ++
		jobsIterator ++
	self.contextActorUID = nil
	self.machine ProcessorFinishedWork self
	return self


Processor ProcessUID <List> uid
	(threadManager AutoreleasePool) ++
	self.commandSystem ContextSwitched
	self.contextActorUID = uid
	self InBackgroundProcessOneJobIfAny
	(threadManager AutoreleasePool) --
	return self
