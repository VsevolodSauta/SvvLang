<Processor> <List> [Retain] contextUID <List> [Retain] contextJobName <ListMap> [Retain] contextJobStageName <Machine> machine <Stack> localNamespaces <Stack> helperStack <ListMap> processorCodes

Processor <Processor> Clone
	return <Processor>

Processor <Processor> DeepClone
	return <Processor>

Processor Destroy
	self.contextUID Release
	self.contextJobName Release
	self.contextJobStageName Release
	self.helperStack Release
	self.localNamespaces Release
	self.processorCodes Release
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
	self.helperStack = <Stack>
	self.processorCodes = <ListMap>
	self.processorCodes AtPut ("Выполнить") &Processor_DoCode
	self.processorCodes AtPut ("Сущность поля сообщения") &Processor_EntityFromMessageFieldCode
	self.processorCodes AtPut ("Идентификатор поля") &Processor_UIDFromFieldCode
	self.processorCodes AtPut ("Текущий объект") &Processor_AddCurrentUIDToStackCode
	self.processorCodes AtPut ("Текущая работа") &Processor_AddCurrentJobToStackCode
	self.processorCodes AtPut ("Текущая стадия") &Processor_AddCurrentJobStageToStackCode
	self.processorCodes AtPut ("Список") &Processor_AddListToStackCode
	self.processorCodes AtPut ("Отображение") &Processor_AddListMapToStackCode
	self.processorCodes AtPut ("Удалить вершину") &Processor_RemoveFromStackCode
	self.processorCodes AtPut ("Добавить сущность в отображение") &Processor_AddEntityToListMapCode
	self.processorCodes AtPut ("Удалить сущность из отображения по ключу") &Processor_RemoveEntityFromListMapByKeyCode
	self.processorCodes AtPut ("Удалить сущность из отображения по значению") &Processor_RemoveEntityFromListMapByValueCode
	self.processorCodes AtPut ("Добавить сущность в список") &Processor_AddEntityToListCode
	self.processorCodes AtPut ("Удалить сущность из списка на позиции") &Processor_RemoveEntityFromListByPositionCode
	self.processorCodes AtPut ("Удалить сущность из списка по значению") &Processor_RemoveEntityFromListByValueCode
	self.processorCodes AtPut ("Добавить сущность в вершину") &Processor_AddEntityToStackCode
	self.processorCodes AtPut ("Дублировать вершину") &Processor_DuplicateTopInStackCode
	self.processorCodes AtPut ("Поменять местами вершинные элементы") &Processor_SwapTopInStackCode
	self.processorCodes AtPut ("Послать сообщение объекту с идентификатором") &Processor_SendMessageToUIDCode
	self.processorCodes AtPut ("Послать сообщение объекту из поля") &Processor_SendMessageToFieldCode
	self.processorCodes AtPut ("Послать сообщение объекту из поля сообщения") &Processor_SendMessageToMessageFieldCode
	self.processorCodes AtPut ("Послать ответ на сообщение") &Processor_SendReplyForMessageCode
	self.processorCodes AtPut ("Вызвать метод с параметрами") &Processor_InvokeMethodCode
	self.processorCodes AtPut ("Определить метод") &Processor_DefineMethodCode
	self.processorCodes AtPut ("Удалить метод с именем") &Processor_UnDefineMethodCode
	self.processorCodes AtPut ("Установить ТВА") &Processor_DefineLocalFieldCode
	self.processorCodes AtPut ("Установить поле работы") &Processor_DefineJobFieldCode
	self.processorCodes AtPut ("Установить поле объекта") &Processor_DefineObjectFieldCode
	self.processorCodes AtPut ("Установить глобальное поле") &Processor_DefineGlobalFieldCode
	self.processorCodes AtPut ("Присвоить полю идентификатор") &Processor_SetFieldCode
	self.processorCodes AtPut ("Перемежить поле прибытия с полем отправления") &Processor_UniteFieldCode
	self.processorCodes AtPut ("Удалить поле") &Processor_UnDefineFieldCode
	self.processorCodes AtPut ("Добавить работу") &Processor_AddJobCode
	self.processorCodes AtPut ("Добавить стадию") &Processor_AddJobStageCode
	self.processorCodes AtPut ("Заблокировать стадию") &Processor_BlockStageCode
	self.processorCodes AtPut ("Разблокировать стадию") &Processor_UnBlockStageCode
	self.processorCodes AtPut ("Заблокировать ожидаемое сообщение") &Processor_BlockMessageSlotCode
	self.processorCodes AtPut ("Разблокировать ожидаемое сообщение") &Processor_UnBlockMessageSlotCode
	self.processorCodes AtPut ("Удалить стадию") &Processor_RemoveJobStageCode
	self.processorCodes AtPut ("Очистить стадии") &Processor_RemoveAllJobStagesCode
	self.processorCodes AtPut ("Очистить ожидаемые сообщения") &Processor_RemoveAllMessageSlotsCode
	self.processorCodes AtPut ("Очистить стадии и ожидаемые сообщения") &Processor_RemoveAllJobStagesAndMessageSlotsCode
	self.processorCodes AtPut ("Добавить ожидаемое сообщение") &Processor_AddMessageSlotCode
	self.processorCodes AtPut ("Удалить ожидаемое сообщение") &Processor_RemoveMessageSlotCode
	self.processorCodes AtPut ("Установить стадии ожидаемое сообщение") &Processor_AttachToStageMessageSlotCode
	self.processorCodes AtPut ("Удалить полученное сообщение") &Processor_RemoveMessageInSlotCode
	self.processorCodes AtPut ("Удалить полученные сообщения") &Processor_RemoveAllReceivedMessagesCode
	self.processorCodes AtPut ("Завершить текущую работу") &Processor_FinishThisJobCode
	return self

Processor Do <ListMap> toDo
	method = self.processorCodes MethodAt (toDo ListAt ("Действие"))
	if method == nil
		console PrintLnString ("Некорректное toDo: Действие не задано либо отсутствует в системе комманд.")
	else
		method Invoke self toDo
	return self

Processor <Object> GetNamedEntityFromToDoOrStack <List> entityName <ListMap> toDo
	object = (toDo At entityName) TempClone
	if object == nil
		object = self.helperStack Pop
	return object
	
Processor DoCode <ListMap> toDo
	action = self GetNamedEntityFromToDoOrStack ("Действие") toDo
	self Do action
	return self

Processor EntityFromMessageFieldCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push ((self ContextJob) JobFieldInMessageSlot fieldName messageSlotName)
	return self

Processor UIDFromFieldCode <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self FieldNameToUID fieldName)
	return self

Processor AddCurrentUIDToStackCode <ListMap> toDo
	self.helperStack Push self.contextUID
	return self

Processor AddCurrentJobToStackCode <ListMap> toDo
	self.helperStack Push self.contextJobName
	return self

Processor AddCurrentJobStageToStackCode <ListMap> toDo
	self.helperStack Push self.contextJobStageName
	return self

Processor AddListToStackCode <ListMap> toDo
	list = <List>
	self.helperStack Push list
	list Release
	return self

Processor AddListMapToStackCode <ListMap> toDo
	listMap = <ListMap>
	self.helperStack Push listMap
	listMap Release
	return self

Processor RemoveFromStackCode <ListMap> toDo
	self.helperStack Remove
	return self

Processor AddEntityToListMapCode <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) AtPut key value
	return self

Processor RemoveEntityFromListMapByKeyCode <ListMap> toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) RemoveKey key
	return self

Processor RemoveEntityFromListMapByValueCode <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	iterator = ((self.helperStack Peek) AsListMap) First
	while iterator NotThisEnd
		if (iterator ThisData) == value
			iterator RemoveThis
			break
	return self

Processor AddEntityToListCode <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	position = toDo NumberAt ("Позиция")
	if position == nil
		((self.helperStack Peek) AsList) Append value
	else
		((self.helperStack Peek) AsList) InsertAtPositionObject position value
	return self

Processor RemoveEntityFromListByPositionCode <ListMap> toDo
	position = self GetNamedEntityFromToDoOrStack ("Позиция") toDo
	if position != nil
		((self.helperStack Peek) AsList) RemoveAt position
	return self

Processor RemoveEntityFromListByValueCode <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	((self.helperStack Peek) AsList) RemoveFirst value
	return self

Processor AddEntityToStackCode <ListMap> toDo
	self.helperStack Push ((toDo ObjectAt ("Значение")) TempClone)
	return self

Processor DuplicateTopInStackCode <ListMap> toDo
	self.helperStack Push ((self.helperStack Peek) TempClone)
	return self

Processor SwapTopInStackCode <ListMap> toDo
	a = self.helperStack Pop
	b = self.helperStack Pop
	self.helperStack Push a
	self.helperStack Push b
	return self

Processor SendMessageToUIDCode <ListMap> toDo
	receiver = self GetNamedEntityFromToDoOrStack ("Получатель") toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self

Processor SendMessageToFieldCode <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	receiver = self FieldNameToUID fieldName
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self

Processor SendMessageToMessageFieldCode <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = (self GetNamedEntityFromToDoOrStack ("Имя поля") toDo) AsList
	messageSlotName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	receiver = (((self ContextJob) JobMessageInMessageSlot messageSlotName) At fieldName)
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self

Processor SendReplyForMessageCode <ListMap> toDo
	reply = (self GetNamedEntityFromToDoOrStack ("Ответ") toDo) AsListMap
	messageName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	message = (self ContextJob) JobMessageInMessageSlot messageName
	receiver = message MessageSender
	reqest = message MessageRequest
	reply = reply TempDeepClone
	reply MessageSetSender self.contextUID
	reply MessageSetReceiver receiver
	reply MessageSetRequest reqest
	reply MessageSetType ("Ответ")
	self SendMessage reply
	return self

Processor InvokeMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	parameters = self GetNamedEntityFromToDoOrStack ("Параметры") toDo
	self InvokeMethodWithParameters methodName parameters
	return self

Processor DefineMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	method = self GetNamedEntityFromToDoOrStack ("Метод") toDo
	(self ContextObject) ObjectSetMethod method methodName
	return self

Processor UnDefineMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	(self ContextObject) ObjectRemoveMethod methodName
	return self

Processor DefineLocalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self.localNamespaces Peek) AsListMap)

Processor DefineJobFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextJob) JobFields)

Processor DefineObjectFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextObject) ObjectFields)

Processor DefineGlobalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo self.machine.globalContext

Processor DefineFieldHelper <ListMap> toDo <ListMap> nameSpace
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.machine DefineFieldHelper uid fieldName nameSpace
	return self

Processor SetFieldCode <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	(self FieldNameToSynonim fieldName) SetUID uid
	return self

Processor UniteFieldCode <ListMap> toDo
	destinationFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля прибытия") toDo
	sourceFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля отправления") toDo
	(self FieldNameToSynonim destinationFieldName) Unite (self FieldNameToSynonim sourceFieldName)
	return self

Processor UnDefineFieldCode <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	locationType = toDo ListAt ("Пространство имен")
	if locationType == nil
		locationType = self FieldNameToNamespaceName fieldName
	place = <ListMap>
	place AtPut ("Имя") fieldName
	place AtPut ("Пространство имен") (self NamespaceNameToNamespace locationType)
	synonim = self FieldNameToSynonim fieldName
	synonim RemoveReference place
	place Release
	return self

Processor AddJobCode <ListMap> toDo
	jobName = self GetNamedEntityFromToDoOrStack ("Имя работы") toDo
	job = self GetNamedEntityFromToDoOrStack ("Работа") toDo
	(self ContextObject) ObjectSetJob job jobName
	return self

Processor AddJobStageCode <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	jobStage = self GetNamedEntityFromToDoOrStack ("Стадия") toDo
	(self ContextJob) JobSetStage jobStage jobStageName
	return self

Processor AddMessageSlotCode <ListMap> toDo
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	message = self GetNamedEntityFromToDoOrStack ("Сообщение") toDo
	(self ContextJob) JobSetMessageSlot message messageName
	return self
	
Processor BlockStageCode <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	((self ContextJob) JobStage stageName) StageSetBlocked
	return self
	
Processor UnBlockStageCode <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	stage = ((self ContextJob) JobStage stageName)
	if (stage StageMessagesCounter) == 0
		stage StageSetReady
	else
		stage StageSetWaiting
	return self

Processor BlockMessageSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	((self ContextJob) JobMessageSlot messageSlotName) MessageSlotBlock
	return self

Processor UnBlockMessageSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	((self ContextJob) JobMessageSlot messageSlotName) MessageSlotOpen
	return self
	

Processor RemoveJobStageCode <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	iterator = (self ContextJob) JobMessageSlotsIterator
	while iterator NotThisEnd
		messageSlot = (iterator Data) AsListMap
		stages = messageSlot MessageSlotStages
		stages RemoveFirst jobStageName
		iterator ++
	(self ContextJob) JobRemoveStage jobStageName
	return self

Processor RemoveMessageSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	if ((self ContextJob) JobMessageInMessageSlot messageSlotName) != nil
		stagesIterator = (self ContextJob) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			if (stage StageMessageSlots) RemoveFirstWithConfirmation messageSlotName
				stage StageDecrementMessagesCounter
				if (stage StageIsWaiting) And ((stage StageMessagesCounter) == 0)
					stage StageSetReady
			stagesIterator ++
	else
		stagesIterator = (self ContextJob) JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			(stage StageMessageSlots) RemoveFirst messageSlotName
			stagesIterator ++
	(self ContextJob) JobRemoveMessageSlot messageSlotName
	return self

Processor RemoveMessageInSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	messageSlot = (self ContextJob) JobMessageSlot messageSlotName
	if (messageSlot MessageSlotMessage) != nil
		messageSlot MessageSlotSetMessage nil
		stagesIterator = messageSlot MessageSlotStagesIterator
		while stagesIterator NotThisEnd
			stage = (self ContextJob) JobStage (stagesIterator ListData)
			stage StageDecrementMessagesCounter
			if stage StageIsReady
				stage StageSetWaiting
			stagesIterator ++
	return nil

Processor RemoveAllReceivedMessagesCode <ListMap> toDo
	messageSlotsIterator = (self ContextJob) JobMessageSlotsIterator
	stagesIterator = (self ContextJob) JobStagesIterator
	while stagesIterator NotThisEnd
		stage = stagesIterator ListMapData
		stage StageSetMessagesCounter ((stage StageMessageSlots) Size)
		stagesIterator ++
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		messageSlot MessageSlotSetMessage nil
		messageSlotsIterator ++
	return self

Processor RemoveAllJobStagesCode <ListMap> toDo
	(self ContextJob) JobRemoveAllStages
	messageSlotsIterator = (self ContextJob) JobMessageSlotsIterator
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		(messageSlot MessageSlotStages) RemoveAll
		messageSlotsIterator ++
	return self

Processor RemoveAllMessageSlotsCode <ListMap> toDo
	(self ContextJob) JobRemoveAllMessageSlots
	jobStagesIterator = (self ContextJob) JobStagesIterator
	while jobStagesIterator NotThisEnd
		jobStage = (jobStagesIterator Data) AsListMap
		(jobStage StageMessageSlots) RemoveAll
		(jobStage StageSetMessagesCounter 0)
		jobStage StageSetBlocked
		jobStagesIterator ++
	return self

Processor RemoveAllJobStagesAndMessageSlotsCode <ListMap> toDo
	(self ContextJob) JobRemoveAllStages
	(self ContextJob) JobRemoveAllMessageSlots
	return self

Processor AttachToStageMessageSlotCode <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self AttachToStageMessageSlot stageName messageName
	return self

Processor FinishThisJobCode <ListMap> toDo
	((self ContextObject) ObjectRemoveJob (self.contextJobName)
	return self








Processor AttachToStageMessageSlot <List> stageName <List> messageName
	stage = (self ContextJob) JobStage stageName
	stagesInMessageSlot = ((self ContextJob) JobMessageSlot messageName) MessageSlotStages
	if stagesInMessageSlot NotContains stageName
		messageSlotsInStage = stage StageMessageSlots
		stagesInMessageSlot Append stageName 
		messageSlotsInStage Append messageName
		stage StageIncrementMessagesCounter
		if stage StageIsReady
			stage StageSetWaiting
	return self


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
	console PrintLnString ("Взятие отсутствующего поля")
	return nil


Processor <List> FieldNameToUID <List> fieldName
	return (self FieldNameToSynonim fieldName) UID


Processor SendMessage <ListMap> message
	uid = message MessageReceiver
	receiver = self.machine ObjectByUID uid
	self ProcessMessageForObject message receiver
	self.machine ScheduleUID uid
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
		console PrintLnString ("Ошибка! Вызов несуществующего метода.")
	else
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
				self Do (iterator ListMapData)
				iterator ++
		self.localNamespaces Pop
	autoreleasePool --
	return self


Processor MessageConfirmsToParameter <ListMap> message <ListMap> parameter
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == "Совпадение"
		return (message At (parameter At ("Ключ"))) == (parameter At ("Значение"))
	elif checkingMethod == "Совпадение с полем"
		return (message At (parameter At ("Ключ"))) == (self FieldNameToSynonim (parameter At ("Значение")))
	elif checkingMethod == "Наличие"
		return (message Contains (parameter At ("Ключ")))
	return false


Processor TryLinkMessageWithMessageSlotAndJob <ListMap> message <ListMap> messageSlot <ListMap> job
	confirms = true
	parametersIterator = (messageSlot ListAt ("Метод идентификации")) First
	while parametersIterator NotThisEnd
		parameter = parametersIterator ListMapData
		if self NotMessageConfirmsToParameter message parameter
			confirms = false
			break
		parametersIterator ++
	if confirms
		messageSlot MessageSlotSetMessage message
		waitingStageNamesIterator = (messageSlot MessageSlotStages) First
		while waitingStageNamesIterator NotThisEnd
			jobStage = (job JobStages) ListMapAt (waitingStageNamesIterator ListData)
			jobStage StageDecrementMessagesCounter
			if ((jobStage StageMessagesCounter) == 0) And (jobStage StageIsWaiting)
				jobStage StageSetReady
			waitingStageNamesIterator ++
	return self


Processor ProcessMessageForObject <ListMap> message <ListMap> object
	jobsIterator = (object ObjectJobs) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		messageSlotsIterator = job JobMessageSlotsIterator
		while messageSlotsIterator NotThisEnd
			messageSlot = messageSlotsIterator ListMapData
			if messageSlot MessageSlotIsOpened
				self TryLinkMessageWithMessageSlotAndJob message messageSlot job
			messageSlotsIterator ++
		jobsIterator ++
	return self


Processor ProcessOneJobIfAny
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
				self.contextJobStageName = nil
				self.contextJobName = nil
				return self
			jobStagesIterator ++
		jobsIterator ++
	return self


Processor ProcessUID <List> uid
	autoreleasePool ++
	self.helperStack Clean
	self.contextUID = uid
	self ProcessOneJobIfAny
	self.contextUID = nil
	autoreleasePool --
	return self


