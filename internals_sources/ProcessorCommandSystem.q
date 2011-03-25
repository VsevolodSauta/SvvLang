<ProcessorCommandSystem> <Stack> helperStack <ListMap> processorCodes <Processor> processor

ProcessorCommandSystem Clone
	return <ProcessorCommandSystem>
	
ProcessorCommandSystem DeepClone
	return <ProcessorCommandSystem>

ProcessorCommandSystem <Comparation> Compare <ProcessorCommandSystem> processorCommandSystem
	return (self Hash) ? (processorCommandSystem Hash)

ProcessorCommandSystem Destroy
	self.helperStack Release
	self.processorCodes Release
	return self Destroy

ProcessorCommandSystem SetProcessor <Processor> processor
	self.processor = processor
	return self

ProcessorCommandSystem Init
	self.helperStack = <Stack>
	self.processorCodes = <ListMap>
	self.processorCodes AtPut ("Выполнить") &ProcessorCommandSystem_CodeDo
	self.processorCodes AtPut ("Сущность поля сообщения") &ProcessorCommandSystem_CodeEntityFromMessageField
	self.processorCodes AtPut ("Идентификатор поля") &ProcessorCommandSystem_CodeUIDFromField
	self.processorCodes AtPut ("Текущий объект") &ProcessorCommandSystem_CodeAddCurrentUIDToStack
	self.processorCodes AtPut ("Текущая работа") &ProcessorCommandSystem_CodeAddCurrentJobToStack
	self.processorCodes AtPut ("Текущая стадия") &ProcessorCommandSystem_CodeAddCurrentJobStageToStack
	self.processorCodes AtPut ("Список") &ProcessorCommandSystem_CodeAddListToStack
	self.processorCodes AtPut ("Отображение") &ProcessorCommandSystem_CodeAddListMapToStack
	self.processorCodes AtPut ("Удалить вершину") &ProcessorCommandSystem_CodeRemoveFromStack
	self.processorCodes AtPut ("Добавить сущность в отображение") &ProcessorCommandSystem_CodeAddEntityToListMap
	self.processorCodes AtPut ("Удалить сущность из отображения по ключу") &ProcessorCommandSystem_CodeRemoveEntityFromListMapByKey
	self.processorCodes AtPut ("Удалить сущность из отображения по значению") &ProcessorCommandSystem_CodeRemoveEntityFromListMapByValue
	self.processorCodes AtPut ("Добавить сущность в список") &ProcessorCommandSystem_CodeAddEntityToList
	self.processorCodes AtPut ("Удалить сущность из списка на позиции") &ProcessorCommandSystem_CodeRemoveEntityFromListByPosition
	self.processorCodes AtPut ("Удалить сущность из списка по значению") &ProcessorCommandSystem_CodeRemoveEntityFromListByValue
	self.processorCodes AtPut ("Добавить сущность в вершину") &ProcessorCommandSystem_CodeAddEntityToStack
	self.processorCodes AtPut ("Дублировать вершину") &ProcessorCommandSystem_CodeDuplicateTopInStack
	self.processorCodes AtPut ("Поменять местами вершинные элементы") &ProcessorCommandSystem_CodeSwapTopInStack
	self.processorCodes AtPut ("Послать сообщение объекту с идентификатором") &ProcessorCommandSystem_CodeSendMessageToUID
	self.processorCodes AtPut ("Послать сообщение объекту из поля") &ProcessorCommandSystem_CodeSendMessageToField
	self.processorCodes AtPut ("Послать сообщение объекту из поля сообщения") &ProcessorCommandSystem_CodeSendMessageToMessageField
	self.processorCodes AtPut ("Послать ответ на сообщение") &ProcessorCommandSystem_CodeSendReplyForMessage
	self.processorCodes AtPut ("Вызвать метод с параметрами") &ProcessorCommandSystem_CodeInvokeMethod
	self.processorCodes AtPut ("Определить метод") &ProcessorCommandSystem_CodeDefineMethod
	self.processorCodes AtPut ("Удалить метод с именем") &ProcessorCommandSystem_CodeUnDefineMethod
	self.processorCodes AtPut ("Установить ТВА") &ProcessorCommandSystem_CodeDefineLocalField
	self.processorCodes AtPut ("Установить поле работы") &ProcessorCommandSystem_CodeDefineJobField
	self.processorCodes AtPut ("Установить поле объекта") &ProcessorCommandSystem_CodeDefineObjectField
	self.processorCodes AtPut ("Установить глобальное поле") &ProcessorCommandSystem_CodeDefineGlobalField
	self.processorCodes AtPut ("Присвоить полю идентификатор") &ProcessorCommandSystem_CodeSetField
	self.processorCodes AtPut ("Перемежить поле прибытия с полем отправления") &ProcessorCommandSystem_CodeUniteField
	self.processorCodes AtPut ("Удалить поле") &ProcessorCommandSystem_CodeUnDefineField
	self.processorCodes AtPut ("Добавить работу") &ProcessorCommandSystem_CodeAddJob
	self.processorCodes AtPut ("Добавить стадию") &ProcessorCommandSystem_CodeAddJobStage
	self.processorCodes AtPut ("Заблокировать стадию") &ProcessorCommandSystem_CodeBlockStage
	self.processorCodes AtPut ("Разблокировать стадию") &ProcessorCommandSystem_CodeUnBlockStage
	self.processorCodes AtPut ("Заблокировать ожидаемое сообщение") &ProcessorCommandSystem_CodeBlockMessageSlot
	self.processorCodes AtPut ("Разблокировать ожидаемое сообщение") &ProcessorCommandSystem_CodeUnBlockMessageSlot
	self.processorCodes AtPut ("Удалить стадию") &ProcessorCommandSystem_CodeRemoveJobStage
	self.processorCodes AtPut ("Очистить стадии") &ProcessorCommandSystem_CodeRemoveAllStages
	self.processorCodes AtPut ("Очистить ожидаемые сообщения") &ProcessorCommandSystem_CodeRemoveAllMessageSlots
	self.processorCodes AtPut ("Очистить стадии и ожидаемые сообщения") &ProcessorCommandSystem_CodeRemoveAllStagesAndMessageSlots
	self.processorCodes AtPut ("Добавить ожидаемое сообщение") &ProcessorCommandSystem_CodeAddMessageSlot
	self.processorCodes AtPut ("Удалить ожидаемое сообщение") &ProcessorCommandSystem_CodeRemoveMessageSlot
	self.processorCodes AtPut ("Установить стадии ожидаемое сообщение") &ProcessorCommandSystem_CodeAttachToStageMessageSlot
	self.processorCodes AtPut ("Удалить сообщения текущей стадии для текущей стадии") &ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForCurrentStage
	self.processorCodes AtPut ("Удалить сообщения текущей стадии") &ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForAllStages
	self.processorCodes AtPut ("Удалить сообщения всех разблокированных стадий") &ProcessorCommandSystem_CodeRemoveAllMessagesOfAllOpenedStages
	self.processorCodes AtPut ("Удалить полученное сообщение") &ProcessorCommandSystem_CodeRemoveMessageInMessageSlot
	self.processorCodes AtPut ("Удалить полученные сообщения") &ProcessorCommandSystem_CodeRemoveAllReceivedMessages
	self.processorCodes AtPut ("Завершить текущую работу") &ProcessorCommandSystem_CodeFinishThisJob
	return self

ProcessorCommandSystem Do <ListMap> toDo
	method = self.processorCodes MethodAt (toDo ListAt ("Действие"))
	if method == nil
		console PrintLnString ("Некорректное toDo: Действие не задано либо отсутствует в системе комманд.")
	else
		method Invoke self toDo
	return self

ProcessorCommandSystem <Object> GetNamedEntityFromToDoOrStack <List> entityName <ListMap> toDo
	object = (toDo At entityName) TempClone
	if object == nil
		object = self.helperStack Pop
	return object



// ============================================
// Обработчики кодов ВМ

ProcessorCommandSystem CodeDo <ListMap> toDo
	action = self GetNamedEntityFromToDoOrStack ("Действие") toDo
	self Do action
	return self

ProcessorCommandSystem CodeEntityFromMessageField <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self.processor EntityFromMessageField fieldName messageSlotName)
	return self


ProcessorCommandSystem CodeUIDFromField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.helperStack Push (self.processor FieldNameToUID fieldName)
	return self


ProcessorCommandSystem CodeAddCurrentUIDToStack <ListMap> toDo
	self.helperStack Push self.processor.contextUID
	return self


ProcessorCommandSystem CodeAddCurrentJobToStack <ListMap> toDo
	self.helperStack Push self.processor.contextJobName
	return self


ProcessorCommandSystem CodeAddCurrentJobStageToStack <ListMap> toDo
	self.helperStack Push self.processor.contextJobStageName
	return self


ProcessorCommandSystem CodeAddListToStack <ListMap> toDo
	list = <List>
	self.helperStack Push list
	list Release
	return self


ProcessorCommandSystem CodeAddListMapToStack <ListMap> toDo
	listMap = <ListMap>
	self.helperStack Push listMap
	listMap Release
	return self


ProcessorCommandSystem CodeRemoveFromStack <ListMap> toDo
	self.helperStack Remove
	return self


ProcessorCommandSystem CodeAddEntityToListMap <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) AtPut key value
	return self


ProcessorCommandSystem CodeRemoveEntityFromListMapByKey <ListMap> toDo
	key = self GetNamedEntityFromToDoOrStack ("Ключ") toDo
	((self.helperStack Peek) AsListMap) RemoveKey key
	return self


ProcessorCommandSystem CodeRemoveEntityFromListMapByValue <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	iterator = ((self.helperStack Peek) AsListMap) First
	while iterator NotThisEnd
		if (iterator ThisData) == value
			iterator RemoveThis
			break
	return self


ProcessorCommandSystem CodeAddEntityToList <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	position = toDo NumberAt ("Позиция")
	if position == nil
		((self.helperStack Peek) AsList) Append value
	else
		((self.helperStack Peek) AsList) InsertAtPositionObject position value
	return self


ProcessorCommandSystem CodeRemoveEntityFromListByPosition <ListMap> toDo
	position = self GetNamedEntityFromToDoOrStack ("Позиция") toDo
	if position != nil
		((self.helperStack Peek) AsList) RemoveAt position
	return self


ProcessorCommandSystem CodeRemoveEntityFromListByValue <ListMap> toDo
	value = self GetNamedEntityFromToDoOrStack ("Значение") toDo
	((self.helperStack Peek) AsList) RemoveFirst value
	return self


ProcessorCommandSystem CodeAddEntityToStack <ListMap> toDo
	self.helperStack Push ((toDo ObjectAt ("Значение")) TempClone)
	return self


ProcessorCommandSystem CodeDuplicateTopInStack <ListMap> toDo
	self.helperStack Push ((self.helperStack Peek) TempClone)
	return self


ProcessorCommandSystem CodeSwapTopInStack <ListMap> toDo
	a = self.helperStack Pop
	b = self.helperStack Pop
	self.helperStack Push a
	self.helperStack Push b
	return self


ProcessorCommandSystem CodeSendMessageToUID <ListMap> toDo
	receiver = self GetNamedEntityFromToDoOrStack ("Получатель") toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	message MessageSetSender self.processor.contextUID
	message MessageSetReceiver receiver
	self.processor SendMessage message
	return self


ProcessorCommandSystem CodeSendMessageToField <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	receiver = self.processor FieldNameToUID fieldName
	message MessageSetSender self.processor.contextUID
	message MessageSetReceiver receiver
	self.processor SendMessage message
	return self


ProcessorCommandSystem CodeSendMessageToMessageField <ListMap> toDo
	message = (self GetNamedEntityFromToDoOrStack ("Сообщение") toDo) AsListMap
	fieldName = (self GetNamedEntityFromToDoOrStack ("Имя поля") toDo) AsList
	messageSlotName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	self.processor SendMessageToMessageField message messageSlotName fieldName
	return self


ProcessorCommandSystem CodeSendReplyForMessage <ListMap> toDo
	reply = (self GetNamedEntityFromToDoOrStack ("Ответ") toDo) AsListMap
	messageName = (self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo) AsList
	self.processor SendReplyForMessage reply messageName
	return self


ProcessorCommandSystem CodeInvokeMethod <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	parameters = self GetNamedEntityFromToDoOrStack ("Параметры") toDo
	self.processor InvokeMethodWithParameters methodName parameters
	return self


ProcessorCommandSystem CodeDefineMethod <ListMap> toDo
	methodName = self GetNamedEntityFromToDoOrStack ("Имя метода") toDo
	method = self GetNamedEntityFromToDoOrStack ("Метод") toDo
	self.processor DefineMethod method methodName
	return self

ProcessorCommandSystem CodeUnDefineMethod <ListMap> toDo
	self.processor UnDefineMethod (self GetNamedEntityFromToDoOrStack ("Имя метода") toDo)
	return self


ProcessorCommandSystem CodeDefineLocalField <ListMap> toDo
	return self DefineFieldHelper toDo ((self.processor.localNamespaces Peek) AsListMap)


ProcessorCommandSystem CodeDefineJobField <ListMap> toDo
	return self DefineFieldHelper toDo ((self.processor ContextJob) JobFields)


ProcessorCommandSystem CodeDefineObjectField <ListMap> toDo
	return self DefineFieldHelper toDo ((self.processor ContextObject) ObjectFields)


ProcessorCommandSystem CodeDefineGlobalField <ListMap> toDo
	return self DefineFieldHelper toDo self.processor.machine.globalContext


ProcessorCommandSystem DefineFieldHelper <ListMap> toDo <ListMap> nameSpace
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	self.processor DefineFieldInNameSpaceWithUID fieldName nameSpace uid
	return self


ProcessorCommandSystem CodeSetField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	uid = self GetNamedEntityFromToDoOrStack ("Идентификатор") toDo
	self.processor SetField fieldName uid
	return self

ProcessorCommandSystem CodeUniteField <ListMap> toDo
	destinationFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля прибытия") toDo
	sourceFieldName = self GetNamedEntityFromToDoOrStack ("Имя поля отправления") toDo
	self.processor UniteField destinationFieldName sourceFieldName
	return self

ProcessorCommandSystem CodeUnDefineField <ListMap> toDo
	fieldName = self GetNamedEntityFromToDoOrStack ("Имя поля") toDo
	locationType = toDo ListAt ("Пространство имен")
	self.processor UnDefineFieldInNamespace fieldName locationType
	return self


ProcessorCommandSystem CodeAddJob <ListMap> toDo
	jobName = self GetNamedEntityFromToDoOrStack ("Имя работы") toDo
	job = self GetNamedEntityFromToDoOrStack ("Работа") toDo
	self.processor AddJobWithName job jobName
	return self

ProcessorCommandSystem CodeFinishThisJob <ListMap> toDo
	self.processor FinishThisJob
	return self


ProcessorCommandSystem CodeAddJobStage <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	jobStage = self GetNamedEntityFromToDoOrStack ("Стадия") toDo
	self.processor AddJobStage jobStage jobStageName
	return self
	
ProcessorCommandSystem CodeAddMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	messageSlot = self GetNamedEntityFromToDoOrStack ("Сообщение") toDo
	self.processor AddMessageSlot messageSlot messageSlotName
	return self
	
ProcessorCommandSystem CodeBlockStage <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	self.processor BlockStage stageName
	return self
	
ProcessorCommandSystem CodeUnBlockStage <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack ("Имя стадии") toDo
	self.processor UnBlockStage stageName
	return self

ProcessorCommandSystem CodeBlockMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack ("Имя сообщения") toDo
	self.processor BlockMessageSlot messageSlotName
	return self


ProcessorCommandSystem CodeUnBlockMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack  ("Имя сообщения") toDo
	self.processor UnBlockMessageSlot messageSlotName
	return self
	

ProcessorCommandSystem CodeRemoveJobStage <ListMap> toDo
	jobStageName = self GetNamedEntityFromToDoOrStack  ("Имя стадии") toDo
	self.processor RemoveJobStage jobStageName
	return self


ProcessorCommandSystem CodeRemoveMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack  ("Имя сообщения") toDo
	self.processor RemoveMessageSlot messageSlotName
	return self

ProcessorCommandSystem CodeRemoveMessageInMessageSlot <ListMap> toDo
	messageSlotName = self GetNamedEntityFromToDoOrStack  ("Имя сообщения") toDo
	self.processor RemoveMessageInMessageSlot messageSlotName
	return self

ProcessorCommandSystem CodeRemoveAllMessagesOfCurrentStageForCurrentStage <ListMap> toDo
	self.processor RemoveAllMessagesOfCurrentStageForCurrentStage
	return self

ProcessorCommandSystem CodeRemoveAllMessagesOfCurrentStageForAllStages <ListMap> toDo
	self.processor RemoveAllMessagesOfCurrentStageForAllStages
	return self

ProcessorCommandSystem CodeRemoveAllMessagesOfAllOpenedStages <ListMap> toDo
	self.processor RemoveAllMessagesOfAllOpenedStages
	return self

ProcessorCommandSystem CodeRemoveAllReceivedMessages <ListMap> toDo
	self.processor RemoveAllReceivedMessages
	return self

ProcessorCommandSystem CodeRemoveAllStages <ListMap> toDo
	self.processor RemoveAllStages
	return self

ProcessorCommandSystem CodeRemoveAllMessageSlots <ListMap> toDo
	self.processor RemoveAllMessageSlots
	return self

ProcessorCommandSystem CodeRemoveAllStagesAndMessageSlots <ListMap> toDo
	self.processor RemoveAllStagesAndMessageSlots
	return self

ProcessorCommandSystem CodeAttachToStageMessageSlot <ListMap> toDo
	stageName = self GetNamedEntityFromToDoOrStack  ("Имя стадии") toDo
	messageName = self GetNamedEntityFromToDoOrStack  ("Имя сообщения") toDo
	self.processor AttachToStageMessageSlot stageName messageName
	return self



