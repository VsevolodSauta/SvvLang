<ExternalCharManipulator> <Machine> machine

ExternalCharManipulator Init
	return self

ExternalCharManipulator Clone
	return self Retain

ExternalCharManipulator DeepClone
	return self Retain

ExternalCharManipulator Destroy
	return self Destroy

ExternalCharManipulator Compare <ExternalCharManipulator> manipulator
	return equal

ExternalCharManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalCharManipulator <List> CreateUIDCharFromUIDActor <List> uid
	job = entitiesFactory CreateEmptyJob

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Код" self &ExternalCharManipulator_GetCode job

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Установить код" self &ExternalCharManipulator_SetCode job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Код")

	actor = self.machine ActorByUID uid
	actor ActorSetJob job "Основная работа символа"
	return uid


ExternalCharManipulator CodeSimpleNumberReceived <Processor> processor
	actor = (processor ContextActor)
	((actor ActorProperty "Символ") AsChar) SetCode (processor EntityFromNamedMessageField "Значение" "Значение простым числом")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetReceiver ((processor ContextJob) JobProperty "Заказчик")
	reply MessageSetTypeAnswer
	reply MessageSetReplySuccess
	reply MessageSetRequest "Установить код"
	processor SendMessage reply
	processor FinishThisJob
	return self


ExternalCharManipulator SetCode <Processor> processor
	request = processor MessageInMessageSlot "Установить код"
	actor = (processor ContextActor)
	code = request At "Код"
	if code TypeIsNumber
		((actor ActorProperty "Символ") AsChar) SetCode code
		reply = entitiesFactory CreateEmptyMessage
		reply MessageSetReplySuccess
		processor SendReplyForMessage reply "Установить код"
	else
		codeRequest = entitiesFactory CreateEmptyMessage
		codeRequest MessageSetReceiver code
		codeRequest MessageSetTypeRequest
		codeRequest MessageSetRequest "Значение простым числом"

		job = entitiesFactory CreateEmptyJob
		job JobSetProperty (request MessageSender) "Заказчик"
		messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalCharManipulator_CodeSimpleNumberReceived job
		processor AddJobWithName job (self.machine GenerateUID)

		processor SendMessage codeRequest
	return self



ExternalCharManipulator GetCode <Processor> processor
	reply = entitiesFactory CreateEmptyMessage
	reply AtPut "Код" ((self.machine ActorsFactory) CreateActorFromObject ((((processor ContextActor) ActorProperty "Символ") AsChar) GetMutableCode))
	processor SendReplyForMessage reply "Код"
	return self
