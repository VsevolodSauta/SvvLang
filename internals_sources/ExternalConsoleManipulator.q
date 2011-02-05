<ExternalConsoleManipulator> <Machine> machine

ExternalConsoleManipulator Init
	return self

ExternalConsoleManipulator Clone
	return self

ExternalConsoleManipulator DeepClone
	return self

ExternalConsoleManipulator Destroy
	return self Destroy
	
ExternalConsoleManipulator <Comparation> Compare <ExternalConsoleManipulator> consoleManipulator
	return equal

ExternalConsoleManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalConsoleManipulator CreateUIDConsoleFromUIDObject <List> uid
	object = self.machine ObjectByUID uid
	object ObjectSetBasicMethod self &ExternalConsoleManipulator_WriteUIDConsoleBasicMethod "Вывести"
	job = entitiesFactory CreateEmptyJob
	messageSlot = entitiesFactory CreateEmptyMessageSlot
	stage = entitiesFactory CreateEmptyJobStage
	stage StageSetMethod "Вывести"
	stage StageSetMessageSlot "Запрос на вывод"
	stage StageIncrementMessagesCounter
	messageSlot MessageSlotSetStage "Вывод"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Тип" "Запрос")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Запрос" "Вывести")
	job JobSetMessageSlot messageSlot "Запрос на вывод"
	job JobSetStage stage "Вывод"
	object ObjectSetJob job "Вывод"
	return uid

ExternalConsoleManipulator WriteUIDConsoleBasicMethod <List> uid <ListMap> parameters <Processor> processor
	string = (processor ContextJob) JobFieldInMessageSlot "Строка" "Запрос на вывод"
	console PrintLnString string
	replyMessage = entitiesFactory CreateEmptyListMap
	replyMessage AtPut "Ответ" "Успех"
	processor SendReplyForMessage replyMessage "Запрос на вывод"
	return self
