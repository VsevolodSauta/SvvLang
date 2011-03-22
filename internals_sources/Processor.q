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
	self.processorCodes AtPut ("Выполнить") &Processor_CodeDo
	self.processorCodes AtPut ("Сущность поля сообщения") &Processor_CodeEntityFromMessageField
	self.processorCodes AtPut ("Идентификатор поля") &Processor_CodeUIDFromField
	self.processorCodes AtPut ("Текущий объект") &Processor_CodeAddCurrentUIDToStack
	self.processorCodes AtPut ("Текущая работа") &Processor_CodeAddCurrentJobToStack
	self.processorCodes AtPut ("Текущая стадия") &Processor_CodeAddCurrentJobStageToStack
	self.processorCodes AtPut ("Список") &Processor_CodeAddListToStack
	self.processorCodes AtPut ("Отображение") &Processor_CodeAddListMapToStack
	self.processorCodes AtPut ("Удалить вершину") &Processor_CodeRemoveFromStack
	self.processorCodes AtPut ("Добавить сущность в отображение") &Processor_CodeAddEntityToListMap
	self.processorCodes AtPut ("Удалить сущность из отображения по ключу") &Processor_CodeRemoveEntityFromListMapByKey
	self.processorCodes AtPut ("Удалить сущность из отображения по значению") &Processor_CodeRemoveEntityFromListMapByValue
	self.processorCodes AtPut ("Добавить сущность в список") &Processor_CodeAddEntityToList
	self.processorCodes AtPut ("Удалить сущность из списка на позиции") &Processor_CodeRemoveEntityFromListByPosition
	self.processorCodes AtPut ("Удалить сущность из списка по значению") &Processor_CodeRemoveEntityFromListByValue
	self.processorCodes AtPut ("Добавить сущность в вершину") &Processor_CodeAddEntityToStack
	self.processorCodes AtPut ("Дублировать вершину") &Processor_CodeDuplicateTopInStack
	self.processorCodes AtPut ("Поменять местами вершинные элементы") &Processor_CodeSwapTopInStack
	self.processorCodes AtPut ("Послать сообщение объекту с идентификатором") &Processor_CodeSendMessageToUID
	self.processorCodes AtPut ("Послать сообщение объекту из поля") &Processor_CodeSendMessageToField
	self.processorCodes AtPut ("Послать сообщение объекту из поля сообщения") &Processor_CodeSendMessageToMessageField
	self.processorCodes AtPut ("Послать ответ на сообщение") &Processor_CodeSendReplyForMessage
	self.processorCodes AtPut ("Вызвать метод с параметрами") &Processor_CodeInvokeMethod
	self.processorCodes AtPut ("Определить метод") &Processor_CodeDefineMethod
	self.processorCodes AtPut ("Удалить метод с именем") &Processor_CodeUnDefineMethod
	self.processorCodes AtPut ("Установить ТВА") &Processor_CodeDefineLocalField
	self.processorCodes AtPut ("Установить поле работы") &Processor_CodeDefineJobField
	self.processorCodes AtPut ("Установить поле объекта") &Processor_CodeDefineObjectField
	self.processorCodes AtPut ("Установить глобальное поле") &Processor_CodeDefineGlobalField
	self.processorCodes AtPut ("Присвоить полю идентификатор") &Processor_CodeSetField
	self.processorCodes AtPut ("Перемежить поле прибытия с полем отправления") &Processor_CodeUniteField
	self.processorCodes AtPut ("Удалить поле") &Processor_CodeUnDefineField
	self.processorCodes AtPut ("Добавить работу") &Processor_CodeAddJob
	self.processorCodes AtPut ("Добавить стадию") &Processor_CodeAddJobStage
	self.processorCodes AtPut ("Заблокировать стадию") &Processor_CodeBlockStage
	self.processorCodes AtPut ("Разблокировать стадию") &Processor_CodeUnBlockStage
	self.processorCodes AtPut ("Заблокировать ожидаемое сообщение") &Processor_CodeBlockMessageSlot
	self.processorCodes AtPut ("Разблокировать ожидаемое сообщение") &Processor_CodeUnBlockMessageSlot
	self.processorCodes AtPut ("Удалить стадию") &Processor_CodeRemoveJobStage
	self.processorCodes AtPut ("Очистить стадии") &Processor_CodeRemoveAllStages
	self.processorCodes AtPut ("Очистить ожидаемые сообщения") &Processor_CodeRemoveAllMessageSlots
	self.processorCodes AtPut ("Очистить стадии и ожидаемые сообщения") &Processor_CodeRemoveAllStagesAndMessageSlots
	self.processorCodes AtPut ("Добавить ожидаемое сообщение") &Processor_CodeAddMessageSlot
	self.processorCodes AtPut ("Удалить ожидаемое сообщение") &Processor_CodeRemoveMessageSlot
	self.processorCodes AtPut ("Установить стадии ожидаемое сообщение") &Processor_CodeAttachToStageMessageSlot
	self.processorCodes AtPut ("Удалить сообщения текущей стадии для текущей стадии") &Processor_CodeRemoveAllMessagesOfCurrentStageForCurrentStage
	self.processorCodes AtPut ("Удалить сообщения текущей стадии") &Processor_CodeRemoveAllMessagesOfCurrentStageForAllStages
	self.processorCodes AtPut ("Удалить сообщения всех разблокированных стадий") &Processor_CodeRemoveAllMessagesOfAllOpenedStages
	self.processorCodes AtPut ("Удалить полученное сообщение") &Processor_CodeRemoveMessageInMessageSlot
	self.processorCodes AtPut ("Удалить полученные сообщения") &Processor_CodeRemoveAllReceivedMessages
	self.processorCodes AtPut ("Завершить текущую работу") &Processor_CodeFinishThisJob
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
	

// ============================================
// Обработчики кодов ВМ

Processor CodeDo <ListMap> toDo
	action = self GetNamedEntityFromToDoOrStack ("Действие") toDo
	self Do action
	return self

Processor CodeEntityFromMessageField <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self EntityFromMessageField fieldName messageSlotName)
	return self


Processor CodeUIDFromField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self FieldNameToUID fieldName)
	return self


Processor CodeAddCurrentUIDToStack <ListMap> toDo
	self.helperStack Push self.contextUID
	return self


Processor CodeAddCurrentJobToStack <ListMap> toDo
	self.helperStack Push self.contextJobName
	return self


Processor CodeAddCurrentJobStageToStack <ListMap> toDo
	self.helperStack Push self.contextJobStageName
	return self


Processor CodeAddListToStack <ListMap> toDo
	list = <List>
	self.helperStack Push list
	list Release
	return self


Processor CodeAddListMapToStack <ListMap> toDo
	listMap = <ListMap>
	self.helperStack Push listMap
	listMap Release
	return self


Processor CodeRemoveFromStack <ListMap> toDo
	self.helperStack Remove
	return self


Processor CodeAddEntityToListMap <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) AtPut key value
	return self


Processor CodeRemoveEntityFromListMapByKey <ListMap> toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) RemoveKey key
	return self


Processor CodeRemoveEntityFromListMapByValue <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	iterator = ((self.helperStack Peek) AsListMap) First
	while iterator NotThisEnd
		if (iterator ThisData) == value
			iterator RemoveThis
			break
	return self


Processor CodeAddEntityToList <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	position = toDo NumberAt ("Позиция")
	if position == nil
		((self.helperStack Peek) AsList) Append value
	else
		((self.helperStack Peek) AsList) InsertAtPositionObject position value
	return self


Processor CodeRemoveEntityFromListByPosition <ListMap> toDo
	position = self GetNamedEntityFromToDoOrStack ("Позиция") toDo
	if position != nil
		((self.helperStack Peek) AsList) RemoveAt position
	return self


Processor CodeRemoveEntityFromListByValue <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	((self.helperStack Peek) AsList) RemoveFirst value
	return self


Processor CodeAddEntityToStack <ListMap> toDo
	self.helperStack Push ((toDo ObjectAt ("Значение")) TempClone)
	return self


Processor CodeDuplicateTopInStack <ListMap> toDo
	self.helperStack Push ((self.helperStack Peek) TempClone)
	return self


Processor CodeSwapTopInStack <ListMap> toDo
	a = self.helperStack Pop
	b = self.helperStack Pop
	self.helperStack Push a
	self.helperStack Push b
	return self


Processor CodeSendMessageToUID <ListMap> toDo
	receiver = self GetNamedEntityFromToDoOrStack ("Получатель") toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self


Processor CodeSendMessageToField <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	receiver = self FieldNameToUID fieldName
	message MessageSetSender self.contextUID
	message MessageSetReceiver receiver
	self SendMessage message
	return self


Processor CodeSendMessageToMessageField <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = (self GetNamedEntityFromToDoOrStack ("Имя поля") toDo) AsList
	messageSlotName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	self SendMessageToMessageField message messageSlotName fieldName
	return self


Processor CodeSendReplyForMessage <ListMap> toDo
	reply = (self GetNamedEntityFromToDoOrStack ("Ответ") toDo) AsListMap
	messageName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	self SendReplyForMessage reply messageName
	return self


Processor CodeInvokeMethod <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	parameters = self GetNamedEntityFromToDoOrStack ("Параметры") toDo
	self InvokeMethodWithParameters methodName parameters
	return self


Processor CodeDefineMethod <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	method = self GetNamedEntityFromToDoOrStack ("Метод") toDo
	self DefineMethod method methodName
	return self

Processor CodeUnDefineMethod <ListMap> toDo
	self UnDefineMethod (self GetNamedEntityFromToDoOrStack ("Имя метода") toDo)
	return self


Processor CodeDefineLocalField <ListMap> toDo
	return self DefineFieldHelper toDo ((self.localNamespaces Peek) AsListMap)


Processor CodeDefineJobField <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextJob) JobFields)


Processor CodeDefineObjectField <ListMap> toDo
	return self DefineFieldHelper toDo ((self ContextObject) ObjectFields)


Processor CodeDefineGlobalField <ListMap> toDo
	return self DefineFieldHelper toDo self.machine.globalContext


Processor DefineFieldHelper <ListMap> toDo <ListMap> nameSpace
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self DefineFieldInNameSpaceWithUID fieldName nameSpace uid
	return self


Processor CodeSetField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	self SetField fieldName uid
	return self

Processor CodeUniteField <ListMap> toDo
	destinationFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля прибытия") toDo
	sourceFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля отправления") toDo
	self UniteField destinationFieldName sourceFieldName
	return self

Processor CodeUnDefineField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	locationType = toDo ListAt ("Пространство имен")
	self UnDefineFieldInNamespace fieldName locationType
	return self


Processor CodeAddJob <ListMap> toDo
	jobName = self GetNamedEntityFromToDoOrStack ("Имя работы") toDo
	job = self GetNamedEntityFromToDoOrStack ("Работа") toDo
	self AddJobWithName job jobName
	return self

Processor CodeFinishThisJob <ListMap> toDo
	self FinishThisJob
	return self


Processor CodeAddJobStage <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	jobStage = self GetNamedEntityFromToDoOrStack ("Стадия") toDo
	self AddJobStage jobStage jobStageName
	return self
	
Processor CodeAddMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	messageSlot = self GetNamedEntityFromToDoOrStack ("Сообщение") toDo
	self AddMessageSlot messageSlot messageSlotName
	return self
	
Processor CodeBlockStage <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	self BlockStage stageName
	return self
	
Processor CodeUnBlockStage <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	self UnBlockStage stageName
	return self

Processor CodeBlockMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self BlockMessageSlot messageSlotName
	return self


Processor CodeUnBlockMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self UnBlockMessageSlot messageSlotName
	return self
	

Processor CodeRemoveJobStage <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	self RemoveJobStage jobStageName
	return self


Processor CodeRemoveMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self RemoveMessageSlot messageSlotName
	return self

Processor CodeRemoveMessageInMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self RemoveMessageInMessageSlot messageSlotName
	return self

Processor CodeRemoveAllMessagesOfCurrentStageForCurrentStage <ListMap> toDo
	self RemoveAllMessagesOfCurrentStageForCurrentStage
	return self

Processor CodeRemoveAllMessagesOfCurrentStageForAllStages <ListMap> toDo
	self RemoveAllMessagesOfCurrentStageForAllStages
	return self

Processor CodeRemoveAllMessagesOfAllOpenedStages <ListMap> toDo
	self RemoveAllMessagesOfAllOpenedStages
	return self

Processor CodeRemoveAllReceivedMessages <ListMap> toDo
	self RemoveAllReceivedMessages
	return self

Processor CodeRemoveAllStages <ListMap> toDo
	self RemoveAllStages
	return self

Processor CodeRemoveAllMessageSlots <ListMap> toDo
	self RemoveAllMessageSlots
	return self

Processor CodeRemoveAllStagesAndMessageSlots <ListMap> toDo
	self RemoveAllStagesAndMessageSlots
	return self

Processor CodeAttachToStageMessageSlot <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	messageName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self AttachToStageMessageSlot stageName messageName
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
				self Do (iterator ListMapData)
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
	self.helperStack Clean
	self.contextUID = uid
	self ProcessOneJobIfAny
	self.contextUID = nil
	autoreleasePool --
	return self

