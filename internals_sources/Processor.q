<Processor> <List> [Retain] contextUID <List> [Retain] contextJobName <ListMap> [Retain] contextJobStageName <Machine> machine <Stack> localNamespaces  <ProcessorCommandSystem> commandSystem <ListMap> contextMessages <ListMap> processorCodes

Processor <Processor> Clone
	return <Processor>

Processor <Processor> DeepClone
	return <Processor>

Processor Destroy
	self.contextUID Release
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

Processor <ListMap> ContextObject
	return self.machine UIDToObject self.contextUID

Processor <ListMap> ContextJob
	return (self ContextObject) ObjectJob self.contextJobName

Processor <ListMap> ContextJobStage
	return (self ContextJob) JobStage self.contextJobStageName

Processor Init
	self.localNamespaces = <Stack>
	self.commandSystem = <ProcessorCommandSystem>
	self.commandSystem SetProcessor self
	return self


// ============================================
// Управление методами

Processor DefineMethod <ListMap> method <List> methodName
	(self ContextObject) ObjectSetMethod method methodName
	return self

Processor UnDefineMethod <List> methodName
	(self ContextObject) ObjectRemoveMethod methodName
	return self


// ============================================
// Управление полями

Processor DefineFieldInNameSpaceWithUID <List> fieldName <ListMap> nameSpace <List> uid
	self.machine DefineFieldHelper uid fieldName nameSpace
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
	(self ContextObject) ObjectSetJob job jobName
	return self

Processor FinishThisJob
	((self ContextObject) ObjectRemoveJob (self.contextJobName)
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
	((self ContextObject) ObjectJob jobName) JobSetStage jobStage jobStageName
	return self

Processor BlockStageInJob <List> stageName <List> jobName
	(((self ContextObject) ObjectJob jobName) JobStage stageName) StageSetBlocked
	return self

Processor UnBlockStageInJob <List> stageName <List> jobName
	stage = (((self ContextObject) ObjectJob jobName) JobStage stageName)
	if (stage StageMessagesCounter) == 0
		stage StageSetReady
	else
		stage StageSetWaiting
	return self

Processor RemoveJobStageInJob <List> jobStageName <List> jobName
	iterator = ((self ContextObject) ObjectJob jobName) JobMessageSlotsIterator
	while iterator NotThisEnd
		messageSlot = (iterator Data) AsListMap
		stages = messageSlot MessageSlotStages
		stages RemoveFirst jobStageName
		iterator ++
	((self ContextObject) ObjectJob jobName) JobRemoveStage jobStageName
	return self

Processor RemoveAllStagesInJob <List> jobName
	((self ContextObject) ObjectJob jobName) JobRemoveAllStages
	messageSlotsIterator = ((self ContextObject) ObjectJob jobName) JobMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		(messageSlot MessageSlotStages) RemoveAll
		messageSlotsIterator ++
	return self


// ============================================
// Управление ожидаемыми сообщениями в произвольной работе

Processor AddMessageSlotInJob <List> messageSlot <List> messageSlotName <List> jobName
	((self ContextObject) ObjectJob jobName) JobSetMessageSlot messageSlot messageSlotName
	return self

Processor BlockMessageSlotInJob <List> messageSlotName <List> jobName
	(((self ContextObject) ObjectJob jobName) JobMessageSlot messageSlotName) MessageSlotBlock
	return self

Processor UnBlockMessageSlotInJob <List> messageSlotName <List> jobName
	(((self ContextObject) ObjectJob jobName) JobMessageSlot messageSlotName) MessageSlotOpen
	return self

Processor RemoveMessageSlotInJob <List> messageSlotName <List> jobName
	if (((self ContextObject) ObjectJob jobName) JobMessageInMessageSlot messageSlotName) != nil
		stagesIterator = ((self ContextObject) ObjectJob jobName) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			if (stage StageMessageSlots) RemoveFirstWithConfirmation messageSlotName
				stage StageDecrementMessagesCounter
				if (stage StageIsWaiting) And ((stage StageMessagesCounter) == 0)
					stage StageSetReady
			stagesIterator ++
	else
		stagesIterator = ((self ContextObject) ObjectJob jobName) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			(stage StageMessageSlots) RemoveFirst messageSlotName
			stagesIterator ++
	((self ContextObject) ObjectJob jobName) JobRemoveMessageSlot messageSlotName
	return self

Processor RemoveAllMessageSlotsInJob <List> jobName
	((self ContextObject) ObjectJob jobName) JobRemoveAllMessageSlots
	jobStagesIterator = ((self ContextObject) ObjectJob jobName) JobStagesIterator
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
	stage = ((self ContextObject) ObjectJob jobName) JobStage stageName
	stagesInMessageSlot = (((self ContextObject) ObjectJob jobName) JobMessageSlot messageName) MessageSlotStages
	if stagesInMessageSlot NotContains stageName
		messageSlotsInStage = stage StageMessageSlots
		stagesInMessageSlot Append stageName
		messageSlotsInStage Append messageName
		stage StageIncrementMessagesCounter
		if stage StageIsReady
			stage StageSetWaiting
	return self

Processor RemoveAllStagesAndMessageSlotsInJob <List> jobName
	((self ContextObject) ObjectJob jobName) JobRemoveAllStages
	((self ContextObject) ObjectJob jobName) JobRemoveAllMessageSlots
	return self


// ============================================
// Управление полученными сообщениями в произвольной работе

Processor RemoveMessageInMessageSlotInJob <List> messageSlotName <List> jobName
	messageSlot = ((self ContextObject) ObjectJob jobName) JobMessageSlot messageSlotName
	if (messageSlot MessageSlotMessage) != nil
	messageSlot MessageSlotRemoveMessage nil
	stagesIterator = messageSlot MessageSlotStagesIterator
	while stagesIterator NotThisEnd
		stage = ((self ContextObject) ObjectJob jobName) JobStage (stagesIterator ListData)
		stage StageDecrementMessagesCounter
		if stage StageIsReady
			stage StageSetWaiting
		stagesIterator ++
	return self

Processor RemoveAllMessagesOfCurrentStageForCurrentStageInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlotName = messageSlotsIterator ListData
		messageSlot = ((self ContextObject) ObjectJob jobName) JobMessageSlot messageSlotName
		messageSlot MessageSlotRemoveMessage nil
		messageSlotsIterator ++
	return self

Processor RemoveAllMessagesOfCurrentStageForAllStagesInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlotName = messageSlotsIterator ListData
		messageSlot = ((self ContextObject) ObjectJob jobName) JobMessageSlot messageSlotName
		message = messageSlot MessageSlotMessage
		messageMessageSlotsIterator = (message MessageAttributesMessageSlots) First
		while messageMessageSlotsIterator NotThisEnd
			messageMessageSlot = ((self ContextObject) ObjectJob jobName) JobMessageSlot (messageMessageSlotsIterator ListData)
			messageMessageSlot MessageSlotRemoveMessage message
			messageMessageSlotsIterator ++
		messageSlotsIterator ++
	return self

Processor RemoveAllMessagesOfAllOpenedStagesInJob <List> jobName
	messageSlotsIterator = (self ContextJobStage) StageMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlot = ((self ContextObject) ObjectJob jobName) JobMessageSlot (messageSlotsIterator ListData)
		if messageSlot MessageSlotIsOpened
			messageSlot MessageSlotRemoveAllMessages
		messageSlotsIterator ++
	return self

Processor RemoveAllReceivedMessagesInJob <List> jobName
	messageSlotsIterator = ((self ContextObject) ObjectJob jobName) JobMessageSlotsIterator
	stagesIterator = ((self ContextObject) ObjectJob jobName) JobStagesIterator
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
// Всякая ерунда (не систематизировано)

Processor <Object> EntityFromNamedMessageField <List> messageName <List> fieldName
	return ((self ContextJob) JobMessageInMessageSlot messageName) ObjectAt fieldName


Processor <ListMap> NamespaceNameToNamespace <List> locationType
	if locationType == "Глобальное поле"
		return self.machine.globalContext
	elif locationType == "Поле объекта"
		return (self ContextObject) ObjectFields
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
	elif ((self ContextObject) ObjectFields) Contains fieldName
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
	candidate = ((self ContextObject) ObjectFields) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate
	console PrintLnString ("!!!!!!!!! Ошибка! Взятие отсутствующего поля.")
	return nil

Processor <Synonim> FieldNameToSynonimInJobObject <List> fieldName <ListMap> job <ListMap> object
	candidate = (job JobFields)  SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = (object ObjectFields) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate
	return nil


Processor <List> FieldNameToUID <List> fieldName
	return (self FieldNameToSynonim fieldName) UID


Processor <Object> EntityFromMessageField <List> fieldName <List> messageSlotName
	return ((self ContextJob) JobFieldInMessageSlot fieldName messageSlotName)


Processor SendMessage <ListMap> message
	uid = message MessageReceiver
	receiver = self.machine ObjectByUID uid
	self ProcessMessageForObject message receiver
	self.machine ScheduleUID uid
	return self


Processor SendMessageToMessageField <ListMap> message <List> messageSlotName <List> fieldName
	receiver = (((self ContextJob) JobMessageInMessageSlot messageSlotName) At fieldName)
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self


Processor SendReplyForMessage <ListMap> replyMessage <List> messageSlotName
	message = (self ContextJob) JobMessageInMessageSlot messageSlotName
	receiver = message MessageSender
	reqest = message MessageRequest
	replyMessage = replyMessage TempDeepClone
	replyMessage MessageSetSender self.contextUID
	replyMessage MessageSetReceiver receiver
	replyMessage MessageSetRequest reqest
	replyMessage MessageSetTypeAnswer
	self SendMessage replyMessage
	return self


Processor InvokeMethodWithParameters <List> methodName <ListMap> parameters
	autoreleasePool ++
	method = (self ContextObject) ObjectMethod methodName
	if method == nil
		console PrintLnString ("!!!!!!!! Ошибка! Вызов несуществующего метода.")
	else
		console PrintString "Процессор вызывает метод: "
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
	autoreleasePool --
	return self


Processor MessageConfirmsToParameterInJobObject <ListMap> message <ListMap> parameter <ListMap> job <ListMap> object
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == "Совпадение"
		return (message At (parameter At ("Ключ"))) == (parameter At ("Значение"))
	elif checkingMethod == "Совпадение с полем"
		synonim = self FieldNameToSynonimInJobObject (parameter At ("Значение")) job object
		if synonim Is nil
			return false
		return (message At (parameter At ("Ключ"))) == (synonim UID)
	elif checkingMethod == "Наличие"
		return (message ContainsKey (parameter At ("Ключ")))
	return false


Processor <Logic> TryLinkMessageWithMessageSlotInJobObject <ListMap> message <ListMap> messageSlot <ListMap> job <ListMap> object <List> messageSlotName <List> jobName
	confirms = true
	parametersIterator = (messageSlot ListAt ("Метод идентификации")) First
	while parametersIterator NotThisEnd
		parameter = parametersIterator ListMapData
		if self NotMessageConfirmsToParameterInJobObject message parameter job object
			confirms = false
			break
		parametersIterator ++
	if confirms
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


Processor ProcessMessageForObject <ListMap> message <ListMap> object
	assigned = false
	console PrintLnString (message MessageRequest)
	jobsIterator = (object ObjectJobs) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		jobName = jobsIterator Key
		messageSlotsIterator = job JobMessageSlotsIterator
		while messageSlotsIterator NotThisEnd
			messageSlot = messageSlotsIterator ListMapData
			messageSlotName = messageSlotsIterator Key
			if messageSlot MessageSlotIsOpened
				assignedRightNow = self TryLinkMessageWithMessageSlotInJobObject message messageSlot job object messageSlotName jobName
				if assignedRightNow
					console PrintString "Сообщение прикреплено к "
					console PrintString jobName
					console PrintString ":"
					console PrintLnString messageSlotName
				assigned = assignedRightNow Or assigned
			messageSlotsIterator ++
		jobsIterator ++
	if assigned Not
		// Скорее всего эту ситуацию надо будет обрабатывать посылкой "неудачного" сообщения в ответ.
		console PrintLnString "!!!!!!!! Ошибка! Сообщение не обработано объектом."
	return self


// Как оно должно работать?
// Объекту посылаются сообщения.
// В какой-то момент времени происходит активация некоторой стадии.
// Далее происходит вызов ассоциированного метода.
// Далее происходит удаление обработанных на стадии сообщений из соответствующих слотов.

// Что должно происходить при удалении сущности А из объекта на этапе выполнения метода?
// Наиболее правильное решение состоит в том, чтобы поддерживать множество удаленных сущностей
// и по завершению метода удалять эти сущности реально.



Processor ProcessOneJobIfAny
	
	// Да, я знаю, что этот метод выглядит ужасно. Но рефакторинга не предвидится в ближайшее время. 07.03.2011
	
	jobsIterator = ((self ContextObject) ObjectJobs) First
	while jobsIterator NotThisEnd
		job = (jobsIterator ListMapData)
		jobStagesIterator = job JobStagesIterator
		while jobStagesIterator NotThisEnd
			jobStage = jobStagesIterator ListMapData
			if jobStage StageIsReady
				self.contextJobStageName = jobStagesIterator Key
				self.contextJobName = jobsIterator Key
				emptyParameters = <ListMap>
				self InvokeMethodWithParameters (jobStage StageMethod) emptyParameters
				emptyParameters Release
				
				// Здесь надо как-то по другому обрабатывать ситуацию, в которой работа была завершена.
				// В любом случае нужен механизм удаления, который будет непосредственно удалять после окончания текущей стадии.
				
				if (self ContextJob) != nil
					messageSlotsIterator = jobStage StageMessageSlotsIterator
					while messageSlotsIterator NotThisEnd
						messageSlotName = messageSlotsIterator ListData
						messageSlot = (self ContextJob) JobMessageSlot messageSlotName
						if messageSlot != nil
							if (messageSlot MessageSlotMessages) NotIsEmpty
								messageSlot MessageSlotRemoveMessage nil
								if (messageSlot MessageSlotMessages) IsEmpty
									slotStagesIterator = messageSlot MessageSlotStagesIterator
									while slotStagesIterator NotThisEnd
										slotStage = (self ContextJob) JobStage (slotStagesIterator ThisData)
										if slotStage != nil
											slotStage StageIncrementMessagesCounter
											if slotStage StageIsReady
												console PrintLnString "Стадия переведена в состояние ожидания"
												slotStage StageSetWaiting
											else
												console PrintLnString "Стадия не была готова."
										else
											console PrintLnString "Стадия, подписанная да это сообщение, удалена."
										slotStagesIterator ++
								else
									console PrintLnString "Ожидаемое сообщение несет более одного сообщения."
							else
								console PrintLnString "Ожидаемое сообщение не несет реальных сообщений."
						else
							console PrintLnString "Ожидаемое сообщение удалено."
						messageSlotsIterator ++
				else
					console PrintLnString "Контекстная работа удалена."
				self.contextJobStageName = nil
				self.contextJobName = nil
				return self
			jobStagesIterator ++
		jobsIterator ++
	return self


Processor ProcessUID <List> uid
	autoreleasePool ++
	
	// SVV: this is workaround... Not very important.
	self.commandSystem.helperStack Clean
	self.contextUID = uid
	self ProcessOneJobIfAny
	self.contextUID = nil
	autoreleasePool --
	return self

