<ExternalJSONParserManipulator@Object> <Machine> machine

ExternalJSONParserManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalJSONParserManipulator CreateUIDJSONParserFromUIDActor <List> uid
	job = entitiesFactory CreateEmptyJob

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Создать объект из простой строки" self &ExternalJSONParserManipulator_CreateEntityFromSimpleString job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Простая строка")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Создать объект из строки" self &ExternalJSONParserManipulator_CreateEntityFromString job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Строка")

	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Код")

	actor = self.machine ActorByUID uid
	actor ActorSetJob job "Основная работа создателя"
	return uid

ExternalJSONParserManipulator InternalCreateEntityFromSimpleString <Processor> processor <List> simpleString <ListMap> reply
	reply MessageSetTypeReply
	result = jsonParser ParseString simpleString
	if result == jsonParser.error
		reply MessageSetReplyFail
		processor SendMessage reply
	else
		reply AtPut "Объект" ((self.machine ActorsFactory) CreateActorFromObject result)
		reply MessageSetReplySuccess
		processor SendMessage reply
	return self

ExternalJSONParserManipulator CreateEntityFromSimpleString <Processor> processor
	message = processor MessageInMessageSlot "Создать объект из простой строки"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetReceiver (message MessageSender)
	reply MessageSetRequest "Создать объект из простой строки"
	return self InternalCreateEntityFromSimpleString processor (message At "Простая строка") reply

ExternalJSONParserManipulator CreateEntityFromString <Processor> processor
	message = processor MessageInMessageSlot "Создать объект из строки"
	stringUID = message At "Строка"

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простой строкой"
	request MessageSetReceiver stringUID

	job = entitiesFactory CreateEmptyJob
	job JobSetProperty (message MessageSender) "Заказчик"
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простой строкой" self &ExternalJSONParserManipulator_SimpleStringReceived job
	processor AddJobWithName job (self.machine GenerateUID)

	processor SendMessage request
	return self

ExternalJSONParserManipulator SimpleStringReceived <Processor> processor
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetReceiver ((processor ContextJob) JobProperty "Заказчик")
	reply MessageSetRequest "Создать объект из строки"
	def self InternalCreateEntityFromSimpleString processor (processor EntityFromNamedMessageField "Значение простой строкой" "Значение") reply
	processor FinishThisJob
