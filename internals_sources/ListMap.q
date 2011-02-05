<ListMap> <ListMapNode> root <Logic> underClonning

ListMap Init
	self.root = <ListMapNode>
	self.underClonning = no
	return self

ListMap <Comparation> Compare <ListMap> listSet
	return self.root ? listSet.root

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

ListMap ResetWithListMap <ListMap> listMap
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

ListMap <Logic> Contains (HasKey Has) <List> list
	node = self.root
	iterator = list First
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
	
ListMap DumpKeys
	iterator = self First
	while iterator NotThisEnd
		console PrintLnString (iterator Key)
		iterator ++
	return self





ListMap ObjectMethods
	return self ListMapAt ("Методы")

ListMap ObjectFields (JobFields)
	return self ListMapAt ("Поля")

ListMap ObjectJobs
	return self ListMapAt ("Работы")

ListMap ObjectProperties
	return self ListMapAt ("Свойства")

ListMap <Synonim> ObjectField (JobFieldWithName) <List> fieldName
	return (self ObjectFields) SynonimAt fieldName

ListMap ObjectFieldUID (JobFieldUIDWithName) <List> fieldName
	return (self ObjectField fieldName) UID

ListMap ObjectMethod <List> methodName
	return (self ObjectMethods) ListMapAt methodName

ListMap ObjectRemoveMethod (ObjectDeleteMethod) <List> methodName
	(self ObjectMethods) RemoveKey methodName
	return self

ListMap ObjectSetMethod <ListMap> method <List> methodName
	(self ObjectMethods) AtPut methodName method
	return self

ListMap ObjectSetMethodBody <List> methodBody <List> methodName
	method = <ListMap>
	method AtPut "Базовый" false
	method AtPut "Тело" methodBody
	(self ObjectMethods) AtPut methodName method
	method Release
	return self

ListMap ObjectSetBasicMethod <Object> entity <Method> basicMethod <List> methodName
	method = <ListMap>
	method AtPut "Базовый" true
	method AtPut "Сущность" entity
	method AtPut "Базовый метод" basicMethod
	(self ObjectMethods) AtPut methodName method
	method Release
	return self

ListMap ObjectSetJob <ListMap> job <List> jobName
	(self ObjectJobs) AtPut jobName job
	return self
	
ListMap ObjectRemoveJob <List> jobName
	(self ObjectJobs) Remove jobName
	return self

ListMap ObjectResetMethods <ListMap> newMethods
	self AtPut "Методы" newMethods // (self ObjectMethods) ResetWithListMap newMethods
	return self

ListMap ObjectResetFields <ListMap> newFields
	self AtPut "Поля" newFields // (self ObjectFields) ResetWithListMap newFields
	return self

ListMap ObjectResetIdentifiers
	((self ObjectProperties) ListAt ("Идентификаторы")) RemoveAll
	return self

ListMap ObjectJob <List> jobName
	return (self ObjectJobs) ListMapAt jobName


ListMap JobStages
	return self ListMapAt ("Стадии")

ListMap JobMessageSlots
	return self ListMapAt ("Сообщения")

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



ListMap <List> MessageSender
	return self ListAt "Отправитель"

ListMap <List> MessageReceiver
	return self ListAt "Получатель"
	
ListMap <List> MessageType
	return self ListAt "Тип"
	
ListMap <List> MessageRequest
	return self ListAt "Запрос"

ListMap <List> MessageReply
	return self ListAt "Ответ"

ListMap MessageSetSender <List> sender
	return self AtPut "Отправитель" sender

ListMap MessageSetReceiver <List> receiver
	return self AtPut "Получатель" receiver
	
ListMap MessageSetType <List> type
	return self AtPut "Тип" type
	
ListMap MessageSetRequest <List> reqest
	return self AtPut "Запрос" reqest

ListMap MessageSetReply <List> reply
	return self AtPut "Ответ" reply




ListMap <List> MessageSlotStages
	return self ListAt ("Стадии")

ListMap MessageSlotMessage
	return self ListMapAt ("Сообщение")

ListMap MessageSlotSetMessage <ListMap> message
	return self AtPut ("Сообщение") message

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


ListMap <Logic> StageContainsMessageSlot <List> messageSlotName
	return (self StageMessageSlots) Contains messageSlotName

ListMap StageSetMethod <List> methodName
	self AtPut "Метод" methodName
	return self
	
ListMap StageSetMessageSlot <List> messageSlotName
	(self StageMessageSlots) AppendIfAbsent messageSlotName
	return self

ListMap <List> StageMessageSlots
	return self ListAt ("Сообщения")

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



