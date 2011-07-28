<ListMap> <ListMapNode> root <Logic> underClonning

ListMap Init
	self.root = <ListMapNode>
	self.underClonning = no
	return self

ListMap <Comparison> Compare <ListMap> listMap
	return self.root ? listMap.root

ListMap Destroy
	self.root Release
	return self Destroy

ListMap Clone
	if self.underClonning
		self DumpKeys
	assert "Under clonning check failed." self.underClonning Not
	self.underClonning = yes
	toReturn = <ListMap>
	toReturn.root Release
	toReturn.root = self.root Clone
	self.underClonning = no
	return toReturn

ListMap DeepClone
	if self.underClonning
		self DumpKeys
	assert "Under clonning check failed." self.underClonning Not
	self.underClonning = yes
	toReturn = <ListMap>
	toReturn.root Release
	toReturn.root = self.root DeepClone
	self.underClonning = no
	return toReturn

ListMap <Logic> Empty
	return (self.root.mapped Not) And (self.root.nextMap Empty)

ListMap Add (AtPut Put +) <List> list object
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			next = <ListMapNode>
			node.nextMap AtPut (iterator ThisData) next
			next Release
			node = next
		iterator ++
	node.mapped = true
	node.mapping = object
	return self

ListMap AddListMap (Merge MergeStrong) <ListMap> listMap
	self.root MergeRecursiveStrong listMap.root
	return self

ListMap Remove (RemoveAt RemoveKey Remove DeleteKey Delete - \) <List> list
	self RemoveKeyWithConfirmation list
	return self

ListMap RemoveAll
	self.root = <ListMapNode>
	return self

ListMap ResetWithListMapDestructive <ListMap> listMap
	self.root = listMap.root
	listMap.root = <ListMapNode>
	return self

ListMap <Logic> RemoveKeyWithConfirmation (RemoveWithConfirmation DeleteKeyWithConfirmation DeleteWithConfirmation -? \?) <List> list
	stack = <Stack>
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			stack Push node
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			stack Release
			return false
		iterator ++
	stack Push node
	node.mapped = false
	node.mapping = nil
	while (stack NotEmpty) And (iterator NotPrevBegin)
		node = (stack Pop) AsListMapNode
		iterator --
		if ((node.nextMap Size) != 0) Or (node.mapped)
			break
		else
			node Release
			parent = ((stack Peek) AsListMapNode)
			parent.nextMap RemoveKey (iterator ThisData)
	stack Release
	return true

ListMap <Object> ObjectAt (AtGet GetValueForKey At GetAt) <List> list
	node = self.root
	iterator = list First
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return nil
		iterator ++
	if node.mapped
		return node.mapping
	else
		return nil

ListMap <Logic> Contains (ContainsKey HasKey Has) <List> list
	node = self.root
	iterator = list First
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return false
		iterator ++
	return node.mapped

ListMap <ListMap> ListMapAt <List> list
	return (self GetAt list) AsListMap

ListMap <List> ListAt <List> list
	return (self GetAt list) AsList

ListMap <Queue> QueueAt <List> list
	return (self GetAt list) AsQueue

ListMap <Logic> LogicAt <List> list
	return (self GetAt list) AsLogic

ListMap <Number> NumberAt <List> list
	return (self GetAt list) AsNumber

ListMap <Synonim> SynonimAt <List> list
	return (self GetAt list) AsSynonim

ListMap <Method> MethodAt <List> list
	return (self GetAt list) AsMethod

ListMap <ListMapIterator> First
	iterator = <ListMapIterator>
	iterator SetListMap self
	iterator ToBegin
	return iterator Autorelease

ListMap <ListMapIterator> Last
	iterator = <ListMapIterator>
	iterator SetListMap self
	iterator ToEnd
	return iterator Autorelease

ListMap <Number> Size (Length Count)
	iterator = self First
	toReturn = 0
	while iterator NotThisEnd
		toReturn ++
		iterator ++
	return toReturn

ListMap DumpKeys
	iterator = self First
	while iterator NotThisEnd
		console PrintLnString (iterator Key)
		iterator ++
	return self

ListMap DumpListToListMap (MessageDump)
	iterator = self First
	while iterator NotThisEnd
		console PrintString "\""
		console PrintString (iterator Key)
		console PrintString "\":"
		if (iterator Value) TypeIsList
			console PrintString "\""
			console PrintString (iterator Value)
			console PrintLnString "\""
		elif (iterator Value) TypeIsNumber
			console PrintLnNumber (iterator Value)
		elif (iterator Value) Is nil
			console PrintLnString "null"
		elif (iterator Value) Is true
			console PrintLnString "true"
		elif (iterator Value) Is false
			console PrintLnString "false"
		else
			console PrintLnString "unknown"
		iterator ++
	return self


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ВНИМАНИЕ! Эти методы должны использоваться только
// процессором. Ни один другой объект не должен их
// использовать.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// ==========================
// Управление объектами

ListMap ActorMethods (JobMethods)
	return self ListMapAt ("Методы")

ListMap ActorFields (JobFields)
	return self ListMapAt ("Поля")

ListMap ActorJobs
	return self ListMapAt ("Работы")

ListMap <ListMapIterator> ActorJobsIterator
	return (self ActorJobs) First

ListMap ActorProperties
	return self ListMapAt ("Свойства")

ListMap <Synonim> ActorField (JobFieldWithName) <List> fieldName
	return (self ActorFields) SynonimAt fieldName

ListMap ActorFieldUID (JobFieldUIDWithName) <List> fieldName
	return (self ActorField fieldName) UID

ListMap ActorMethod (JobMethod) <List> methodName
	return (self ActorMethods) ListMapAt methodName

ListMap ActorRemoveMethod (ActorDeleteMethod JobRemoveMethod) <List> methodName
	(self ActorMethods) RemoveKey methodName
	return self

ListMap ActorSetMethod (JobSetMethod) <ListMap> method <List> methodName
	(self ActorMethods) AtPut methodName method
	return self

ListMap ActorSetMethodBody (JobSetMethodBody) <List> methodBody <List> methodName
	method = <ListMap>
	method AtPut "Базовый" false
	method AtPut "Тело" methodBody
	(self ActorMethods) AtPut methodName method
	method Release
	return self

ListMap ActorSetBasicMethod (JobSetBasicMethod) <Object> entity <Method> basicMethod <List> methodName
	method = <ListMap>
	method AtPut "Базовый" true
	method AtPut "Сущность" entity
	method AtPut "Базовый метод" basicMethod
	(self ActorMethods) AtPut methodName method
	method Release
	return self

ListMap ActorSetJob <ListMap> job <List> jobName
	(self ActorJobs) AtPut jobName job
	return self

ListMap ActorSetProperty (JobSetProperty) value <List> propertyName
	(self ActorProperties) AtPut propertyName value
	return self

ListMap ActorRemoveJob <List> jobName
	(self ActorJobs) Remove jobName
	return self

ListMap ActorResetMethodsDestructive <ListMap> newMethods
	self AtPut "Методы" newMethods // (self ActorMethods) ResetWithListMapDestructive newMethods
	return self

ListMap ActorResetFieldsDestructive <ListMap> newFields
	self AtPut "Поля" newFields // (self ActorFields) ResetWithListMapDestructive newFields
	return self

ListMap ActorResetJobsDestructive <ListMap> newJobs
	self AtPut "Работы" newJobs // (self ActorJobs) ResetWithListMapDestructive newJobs
	jobsIterator = self ActorJobsIterator
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		messageSlotsIterator = job JobMessageSlotsIterator
		stagesIterator = job JobStagesIterator
		while stagesIterator NotThisEnd
			stage = stagesIterator ListMapData
			stage StageSetMessagesCounter ((stage StageMessageSlots) Size)
			if stage StageIsReady
				if (stage StageMessagesCounter) != 0
					stage StageSetWaiting
			stagesIterator ++
		while messageSlotsIterator NotThisEnd
			messageSlot = messageSlotsIterator ListMapData
			messageSlot MessageSlotRemoveAllMessages
			messageSlotsIterator ++
		jobsIterator ++
	return self

ListMap ActorRemoveAllIdentifiers
	((self ActorProperties) ListAt ("Идентификаторы")) RemoveAll
	return self

ListMap ActorJob <List> jobName
	return (self ActorJobs) ListMapAt jobName


ListMap <Object> ActorProperty (JobProperty) <List> propertyName
	return (self ActorProperties) ObjectAt propertyName

ListMap <List> ActorNotificationRequests
	return self ActorProperty "Запросы на оповещение"

ListMap ActorAddNotificationRequest <ListMap> notificationRequest
	(self ActorNotificationRequests) Append notificationRequest
	return self

ListMap <ListIterator> ActorNotificationRequestsIterator
	return (self ActorNotificationRequests) First


// ==========================
// Управление работами

ListMap JobStages
	return self ListMapAt ("Стадии")

ListMap JobMessageSlots
	return self ListMapAt ("Ожидаемые сообщения")

ListMap JobStage <List> stageName
	return (self JobStages) ListMapAt stageName

ListMap JobFieldInMessageSlot <List> fieldName <List> messageSlotName
	return (self JobMessageInMessageSlot messageSlotName) ObjectAt fieldName

ListMap JobMessageSlot <List> messageSlotName
	return (self JobMessageSlots) ListMapAt messageSlotName

ListMap JobMessageInMessageSlot <List> messageSlotName
	return (self JobMessageSlot messageSlotName) MessageSlotMessage

ListMap JobSetStage <ListMap> stage <List> stageName
	(self JobStages) AtPut stageName stage
	return self

ListMap JobRemoveStage <List> stageName
	(self JobStages) Remove stageName
	return self

ListMap JobRemoveStageAndMessageSlots <List> stageName
	stage = (self JobStages) ListMapAt stageName
	if stage == nil
		return self
	stageMessageSlotsIterator = stage StageMessageSlotsIterator
	while stageMessageSlotsIterator NotThisEnd
		messageSlotName = stageMessageSlotsIterator ListData
		if ((((self JobMessageSlot messageSlotName) MessageSlotStages) Size) == 1
			self JobRemoveMessageSlot messageSlotName
		else
			((self JobMessageSlot messageSlotName) MessageSlotStages) RemoveFirst stageName
		stageMessageSlotsIterator ++
	(self JobStages) RemoveAt stageName
	return self

ListMap JobSetMessageSlot <ListMap> messageSlot <List> messageSlotName
	(self JobMessageSlots) AtPut messageSlotName messageSlot
	return self

ListMap JobRemoveMessageSlot <List> messageSlotName
	(self JobMessageSlots) Remove messageSlotName
	return self

ListMap <ListMapIterator> JobMessageSlotsIterator
	return (self JobMessageSlots) First

ListMap <ListMapIterator> JobStagesIterator
	return (self JobStages) First

ListMap JobRemoveAllStages
	(self JobStages) RemoveAll
	return self

ListMap JobRemoveAllMessageSlots
	(self JobMessageSlots) RemoveAll
	return self

ListMap JobCreateStageWithNameMethodRequestMessageSlot <List> stageName <List> methodName <List> messageSlotName <List> messageSlotRequestName
	stage = entitiesFactory CreateEmptyJobStage
	stage StageSetMethod methodName
	stage StageSetMessageSlot messageSlotName
	stage StageIncrementMessagesCounter
	self JobSetStage stage stageName

	messageSlot = entitiesFactory CreateEmptyMessageSlot
	messageSlot MessageSlotSetStage stageName
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Тип" "Запрос")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Запрос" messageSlotRequestName)
	self JobSetMessageSlot messageSlot messageSlotName

	return self

ListMap JobCreateStageWithNameMethodMessageSlotNameAndEntity <List> stageName <List> methodName <List> messageSlotName <ListMap> messageSlot
	stage = entitiesFactory CreateEmptyJobStage
	stage StageSetMethod methodName
	stage StageSetMessageSlot messageSlotName
	stage StageIncrementMessagesCounter
	stage StageSetWaiting
	messageSlot MessageSlotSetStage stageName
	self JobSetStage stage stageName
	self JobSetMessageSlot messageSlot messageSlotName
	return self


// ==========================
// Управление сообщениями

ListMap <List> MessageSender
	return self ListAt "Отправитель"

ListMap <List> MessageReceiver
	return self ListAt "Получатель"

ListMap <List> MessageType
	return self ListAt "Тип"

ListMap <List> MessageRequest
	return self ListAt "Запрос"

ListMap MessageSetSender <List> sender
	return self AtPut "Отправитель" sender

ListMap MessageSetReceiver <List> receiver
	return self AtPut "Получатель" receiver

ListMap MessageSetType <List> type
	return self AtPut "Тип" type

ListMap MessageSetTypeReply (MessageSetTypeAnswer)
	return self MessageSetType "Ответ"

ListMap MessageSetTypeRequest
	return self MessageSetType "Запрос"

ListMap MessageSetTypeNotification
	return self MessageSetType "Оповещение"

ListMap MessageSetRequest <List> request
	return self AtPut "Запрос" request

ListMap MessageSetReply (MessageSetAnswer) <List> reply
	return self AtPut "Ответ" reply

ListMap MessageSetReplySuccess (MessageSetAnswerSuccess)
	return self MessageSetReply "Успех"

ListMap MessageSetReplyFail (MessageSetAnswerFail)
	return self MessageSetReply "Неудача"

ListMap <List> MessageReply (MessageAnswer)
	return self ListAt "Ответ"

ListMap <Logic> MessageReplyIsSuccess (MessageAnswerIsSuccess)
	return (self MessageReply) == "Успех"

ListMap <Logic> MessageReplyIsFail (MessageAnswerIsFail)
	return (self MessageReply) == "Неудача"

ListMap MessageSetJobNameAndMessageSlotName <List> jobName <List> messageSlotName
	listmap = entitiesFactory CreateEmptyListMap
	listmap AtPut "Работа" jobName
	listmap AtPut "Ожидаемое сообщение" messageSlotName
	((self ListMapAt "Свойства") ListAt "Ожидаемые сообщения") Append listmap
	return self

ListMap MessageAttributesMessageSlots
	return ((self ListMapAt "Свойства") ListAt "Ожидаемые сообщения")


// =================================
// Управление ожидаемыми сообщениями

ListMap <List> MessageSlotStages
	return self ListAt ("Стадии")

ListMap <ListIterator> MessageSlotStagesIterator
	return (self ListAt ("Стадии")) First

ListMap MessageSlotMessage
	return (self ListAt ("Сообщения")) PeekFront

ListMap <List> MessageSlotMessages
	return (self ListAt ("Сообщения"))

ListMap MessageSlotSetMessage <ListMap> message
	list = self ListAt ("Сообщения")
	list PushBack message
	return self

ListMap MessageSlotRemoveMessage <ListMap> message
	list = self ListAt ("Сообщения")
	if message == nil
		if list NotIsEmpty
			list RemoveFront
	else
		list RemoveFirstExactlySame message
	return self

ListMap MessageSlotRemoveAllMessages
	list = <List>
	self AtPut ("Сообщения") list
	list Release
	return self

ListMap <Object> MessageSlotField <List> fieldName
	return (self MessageSlotMessage) ObjectAt fieldName

ListMap MessageSlotSetStage <List> stageName
	(self MessageSlotStages) AppendIfAbsent stageName
	return self

ListMap <List> MessageSlotConditions
	return self ListAt ("Метод идентификации")

ListMap MessageSlotSetCondition <ListMap> condition
	(self MessageSlotConditions) Append condition
	return self

ListMap <Logic> MessageSlotIsBlocked
	return (self At "Состояние") == "Заблокировано"

ListMap <Logic> MessageSlotIsClosed
	return (self At "Состояние") == "Закрыто"

ListMap <Logic> MessageSlotIsOpened
	return (self At "Состояние") == "Открыто"

ListMap MessageSlotBlock
	self AtPut "Состояние" "Заблокировано"
	return self

ListMap MessageSlotOpen
	self AtPut "Состояние" "Открыто"
	return self

ListMap MessageSlotClose
	self AtPut "Состояние" "Закрыто"
	return self

// ==========================
// Управление стадиями

ListMap <Logic> StageContainsMessageSlot <List> messageSlotName
	return (self StageMessageSlots) Contains messageSlotName

ListMap StageSetMethod <List> methodName
	self AtPut "Метод" methodName
	return self

ListMap StageSetMessageSlot <List> messageSlotName
	(self StageMessageSlots) AppendIfAbsent messageSlotName
	return self

ListMap <List> StageMessageSlots
	return self ListAt ("Ожидаемые сообщения")

ListMap <ListIterator> StageMessageSlotsIterator
	return (self ListAt ("Ожидаемые сообщения")) First

ListMap <List> StageMethod
	return self ListAt ("Метод")

ListMap StageIncrementMessagesCounter
	(self NumberAt ("Необходимо сообщений")) ++
	return self

ListMap StageDecrementMessagesCounter
	(self NumberAt ("Необходимо сообщений")) --
	return self

ListMap <Number> StageMessagesCounter
	return (self NumberAt ("Необходимо сообщений"))

ListMap StageSetMessagesCounter <Number> newMessagesCounter
	self AtPut ("Необходимо сообщений") newMessagesCounter
	return self

ListMap StageSetBlocked
	return self AtPut "Состояние" "Заблокировано"

ListMap StageSetReady
	return self AtPut "Состояние" "Готово"

ListMap StageSetWaiting
	return self AtPut "Состояние" "Ожидание"

ListMap <Logic> StageIsWaiting
	return (self At "Состояние") == "Ожидание"

ListMap <Logic> StageIsReady
	return (self At "Состояние") == "Готово"

ListMap <Logic> StageIsBlocked
	return (self At "Состояние") == "Заблокировано"
