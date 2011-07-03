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

ExternalConsoleManipulator CreateUIDConsoleFromUIDActor <List> uid
	actor = self.machine ActorByUID uid
	actor ActorSetBasicMethod self &ExternalConsoleManipulator_WriteUIDConsoleBasicMethod "Вывести"
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
	actor ActorSetJob job "Вывод"
	return uid

ExternalConsoleManipulator WriteUIDConsoleBasicMethod <Processor> processor
	string = processor EntityFromNamedMessageField "Запрос на вывод" "Строка" 
	console PrintLnString string
	replyMessage = entitiesFactory CreateEmptyMessage
	replyMessage MessageSetReplySuccess
	processor SendReplyForMessage replyMessage "Запрос на вывод"
	return self


