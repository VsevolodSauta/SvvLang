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
	return (self ContextObjectJobs) ListMapAt self.contextJobName

Processor <ListMap> ContextJobStage
	return (self ContextJobStages) ListMapAt self.contextJobStageName

Processor <ListMap> ContextObjectMethods
	return (self ContextObject) ListMapAt ("Методы")

Processor <ListMap> ContextObjectJobs
	return (self ContextObject) ListMapAt ("Работы")

Processor <ListMap> ContextObjectProperties
	return (self ContextObject) ListMapAt ("Свойства")

Processor <ListMap> ContextJobStages
	return (self ContextJob) ListMapAt ("Стадии")

Processor <ListMap> ContextJobMessageSlots (ContextJobExpectedMessages)
	return (self ContextJob) ListMapAt ("Ожидаемые сообщения")

Processor <ListMap> ContextJobMessageSlot <List> messageSlotName
	return (self ContextJobMessageSlots) ListMapAt messageSlotName

Processor <ListMap> ContextJobMessage <List> messageName
	return (self ContextJobMessageSlot messageName) ListMapAt ("Сообщение")

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
	console PrintLnString (toDo ListAt ("Действие"))
	method = self.processorCodes MethodAt (toDo ListAt ("Действие"))
	if method == nil
		console PrintLnString ("Некорректное toDo: Действие не задано либо отсутствует в системе комманд.")
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
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	message = self ContextJobMessage messageName
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self EntityFromMessageField message fieldName)
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
	position = toDo At ("Позиция")
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
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	receiver = self GetNamedEntityFromToDoOrStack ("Получатель") toDo
	message AtPut ("Отправитель") self.contextUID
	message AtPut ("Получатель") receiver
	self SendMessage message
	return self

Processor SendMessageToFieldCode <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	receiver = self FieldNameToUID fieldName
	message AtPut ("Отправитель") self.contextUID
	message AtPut ("Получатель") receiver
	self SendMessage message
	return self

Processor SendReplyForMessageCode <ListMap> toDo
	reply = (self GetNamedEntityFromToDoOrStack ("Ответ") toDo) AsListMap
	messageName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsListMap
	message = (((self ContextJobMessageSlots) ListMapAt messageName) ListMapAt "Сообщение")
	receiver = message ListAt "Отправитель"
	reqest = message ListAt "Запрос"
	message AtPut ("Отправитель") self.contextUID
	message AtPut ("Получатель") receiver
	message AtPut ("Запрос") reqest
	message AtPut ("Тип") ("Ответ")
	self SendMessage message
	return self

Processor InvokeMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	parameters = self GetNamedEntityFromToDoOrStack ("Параметры") toDo
	self InvokeMethodWithParameters methodName parameters
	return self

Processor DefineMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	method = self GetNamedEntityFromToDoOrStack ("Метод") toDo
	(self ContextObjectMethods) AtPut methodName method
	return self

Processor UnDefineMethodCode <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	(self ContextObjectMethods) RemoveAt methodName
	return self

Processor DefineLocalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self.localNamespaces Peek) AsListMap)

Processor DefineJobFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextJob) ListMapAt ("Поля"))

Processor DefineObjectFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextObject) ListMapAt ("Поля"))

Processor DefineGlobalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo self.machine.globalContext

Processor DefineFieldHelper <ListMap> toDo <ListMap> nameSpace
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	synonim = <Synonim>
	synonim SetUID uid
	reference = <ListMap>
	reference AtPut ("Пространство имен") nameSpace
	reference AtPut ("Имя поля") fieldName
	synonim AddReference reference
	reference Release
	synonim Release
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
	(self ContextObjectJobs) AtPut jobName job
	return self

Processor AddJobStageCode <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	jobStage = self GetNamedEntityFromToDoOrStack ("Стадия") toDo
	(self ContextJobStages) AtPut jobStageName jobStage
	return self

Processor AddMessageSlotCode <ListMap> toDo
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	message = self GetNamedEntityFromToDoOrStack ("Сообщение") toDo
	(self ContextJobMessageSlots) AtPut messageName message
	return self

Processor RemoveJobStageCode <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	messageSlots = self ContextJobMessageSlots
	iterator = messageSlots First
	while iterator NotThisEnd
		messageSlot = (iterator Data) AsListMap
		stages = messageSlot ListAt ("Ожидающие стадии")
		stages RemoveFirst jobStageName
		iterator ++
	(self ContextJob) RemoveKey jobStageName
	return self

Processor RemoveMessageSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	messageSlot = (self ContextJobMessageSlot messageSlotName)
	mustDecrement = (messageSlot At "Сообщение") != nil
	stagesIterator = (self ContextJobStages) First
	if mustDecrement
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			if (stage ListAt "Ожидаемые сообщения") RemoveFirstWithConfirmation messageSlotName
				(stage NumberAt "Необходимо сообщений") --
			stagesIterator ++
	else
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			stage ListAt "Ожидаемые сообщения") RemoveFirst
			stagesIterator ++
	return self

Processor RemoveMessageInSlotCode <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	messageSlot = (self ContextJobMessageSlot messageSlotName)
	if (messageSlot At "Сообщение") != nil
		messageSlot AtPut "Сообщение" nil
		stagesIterator = (self ContextJobStages) First
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			if (stage ListAt "Ожидаемые сообщения") Contains messageSlotName
				(stage NumberAt "Необходимо сообщений") --
			stagesIterator ++
	return nil

Processor RemoveAllReceivedMessagesCode <ListMap> toDo
	messageSlots = self ContextJobMessageSlots
	stages = self ContextJobStages
	stagesIterator = stages First
	while stagesIterator NotThisEnd
		stage = stagesIterator ListMapData
		stage AtPut ("Необходимо сообщений") ((stage ListAt "Ожидаемые сообщения") Size)
		stagesIterator ++
	messageSlotsIterator = messageSlots First
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		messageSlot AtPut ("Сообщение") nil
		messageSlotsIterator ++
	return self

Processor RemoveAllJobStagesCode <ListMap> toDo
	(self ContextJobStages) RemoveAll
	messageSlots = self ContextJobMessageSlots
	messageSlotsIterator = messageSlots First
	while messageSlotsIterator NotThisEnd
		messageSlot = messageSlotsIterator ListMapData
		(messageSlot ListAt "Ожидающие стадии") RemoveAll
		messageSlotsIterator ++
	return self

Processor RemoveAllMessageSlotsCode <ListMap> toDo
	(self ContextJobMessageSlots) RemoveAll
	jobStagesIterator = (self ContextJobStages) First
	while jobStagesIterator NotThisEnd
		jobStage = (jobStagesIterator Data) AsListMap
		(jobStage ListAt ("Ожидаемые сообщения")) RemoveAll
		(jobStage AtPut ("Необходимо сообщений") 0)
		jobStagesIterator ++
	return self

Processor RemoveAllJobStagesAndMessageSlotsCode <ListMap> toDo
	(self ContextJobStages) RemoveAll
	(self ContextJobMessageSlots) RemoveAll
	return self

Processor AttachToStageMessageSlotCode <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self AttachToStageMessageSlot stageName messageName
	return self

Processor FinishThisJobCode <ListMap> toDo
	(self ContextObjectJobs) RemoveAt (self.contextJobName)
	return self

Processor AttachToStageMessageSlot <List> stageName <List> messageName
	stage = (self ContextJobStages) ListMapAt stageName
	stagesInMessageSlot = (self ContextJobMessageSlots) ListAt messageName
	if stagesInMessageSlot NotContains stageName
		messageSlotsInStage = stage ListAt ("Ожидаемые сообщения")
		stagesInMessageSlot Append stageName
		messageSlotsInStage Append messageName
		(stage NumberAt ("Необходимо сообщений")) ++
	return self

Processor <Object> EntityFromMessageField <ListMap> message <List> name
	return message ObjectAt name

Processor <Object> EntityFromNamedMessageField <List> messageName <List> fieldName
	return (((self ContextJobMessageSlots) ListMapAt messageName) ListMapAt ("Сообщение")) ObjectAt fieldName

Processor <ListMap> NamespaceNameToNamespace <List> locationType
	if locationType == "Глобальное поле"
		return self.machine.globalContext
	elif locationType == "Поле объекта"
		return (self ContextObject) ListMapAt ("Поля")
	elif locationType == "Поле работы"
		return (self ContextJob) ListMapAt ("Поля")
	elif locationType == "Локальное поле"
		return self.localNamespaces Peek
	return nil

Processor <List> FieldNameToNamespaceName <List> fieldName
	candidate = ((self.localNamespaces Peek) AsListMap) ObjectAt fieldName
	if candidate != nil
		return ("Локальное поле")
	candidate = ((self ContextJob) ListMapAt ("Поля"))  ObjectAt fieldName
	if candidate != nil
		return ("Поле работы")
	candidate = ((self ContextObject) ListMapAt ("Поля")) ObjectAt fieldName
	if candidate != nil
		return ("Поле объекта")
	candidate = (self.machine.globalContext) ObjectAt fieldName
	if candidate != nil
		return ("Глобальное поле")
	else
		return ("Нет такого поля")

Processor <Synonim> FieldNameToSynonim <List> fieldName
	candidate = ((self.localNamespaces Peek) AsListMap) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = ((self ContextJob) ListMapAt ("Поля"))  SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = ((self ContextObject) ListMapAt ("Поля")) SynonimAt fieldName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt fieldName
	if candidate != nil
		return candidate
	console PrintLnString ("Взятие отсутствующего поля")
	return nil

Processor <List> FieldNameToUID <List> fieldName
	synonim = self FieldNameToSynonim fieldName
	return synonim UID

Processor SendMessage <ListMap> message
	uid = message ListAt ("Получатель")
	receiver = self.machine ObjectByUID uid
	self ProcessMessageForObject message receiver
	self.machine ScheduleUID uid
	return self

Processor InvokeMethodWithParameters <List> methodName <ListMap> parameters
	autoreleasePool ++
	method = (self ContextObjectMethods) ListMapAt methodName
	if method == nil
		console PrintLnString ("Ошибка! Вызов несуществующего метода.")
	else
		if method LogicAt ("Базовый")
			basicMethod = method MethodAt ("Базовый метод")
			objectEntity = method ObjectAt ("Сущность")
			basicMethod Invoke objectEntity self.contextUID parameters self
		else
			namespace = <ListMap>
			self.localNamespaces Push namespace
			namespace AddListMap parameters
			namespace Release
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
	if checkingMethod == ("Совпадение")
		if (message At (parameter At ("Ключ"))) == (parameter At ("Значение"))
			return true
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
		messageSlot AtPut ("Сообщение") message
		waitingStageNamesIterator = (messageSlot ListAt ("Ожидающие стадии")) First
		while waitingStageNamesIterator NotThisEnd
			jobStage = (job ListMapAt ("Стадии")) ListMapAt (waitingStageNamesIterator ListData)
			msgNeeded = (jobStage NumberAt ("Необходимо сообщений"))
			msgNeeded --
			waitingStageNamesIterator ++
	return self


Processor ProcessMessageForObject <ListMap> message <ListMap> object
	jobsIterator = (object ListMapAt ("Работы")) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		messageSlotsIterator = (job ListMapAt ("Ожидаемые сообщения")) First
		while messageSlotsIterator NotThisEnd
			self TryLinkMessageWithMessageSlotAndJob message (messageSlotsIterator ListMapData) job
			messageSlotsIterator ++
		jobsIterator ++
	return self


Processor ProcessOneJobIfAny
	jobsIterator = (self ContextObjectJobs) First
	while jobsIterator NotThisEnd
		job = (jobsIterator ListMapData)
		jobStagesIterator = (job ListMapAt ("Стадии")) First
		while jobStagesIterator NotThisEnd
			jobStage = jobStagesIterator ListMapData
			if (jobStage NumberAt ("Необходимо сообщений")) == 0
				self.contextJobStageName = jobStagesIterator Key
				self.contextJobName = jobsIterator Key
				emptyParameters = <ListMap>
				self InvokeMethodWithParameters (jobStage ListAt ("Метод")) emptyParameters
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
