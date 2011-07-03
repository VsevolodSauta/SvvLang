<ExternalListMapManipulator> <Machine> machine

ExternalListMapManipulator Init
	return self

ExternalListMapManipulator Clone
	return self Retain

ExternalListMapManipulator DeepClone
	return self Retain

ExternalListMapManipulator Destroy
	return self Destroy

ExternalListMapManipulator Compare <ExternalListMapManipulator> manipulator
	return equal

ExternalListMapManipulator SetMachine <Machine> machine
	self.machine = machine
	return self


ExternalListMapManipulator <List> CreateUIDListMapFromUIDActor <List> uid
	job = entitiesFactory CreateEmptyJob

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Послать всем объектам" self &ExternalListMapManipulator_SendToAll job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Сообщение")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Действия с ответами")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Объект на позиции" self &ExternalListMapManipulator_AtGet job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Послать сообщение объекту на позиции" self &ExternalListMapManipulator_AtSend job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Добавить объект на позицию" self &ExternalListMapManipulator_AtInsert job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Объект")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Размер" self &ExternalListMapManipulator_Size job

	actor = self.machine ActorByUID uid
	actor ActorSetJob job "Основная работа отображение списков"
	return uid


ExternalListMapManipulator Size <Processor> processor
	message = entitiesFactory CreateEmptyMessage
	message AtPut "Размер" ((self.machine ActorsFactory) CreateActorFromObject ((((processor ContextActor) ActorProperty "Отображение списков") AsListMap) Size))
	processor SendReplyForMessage message "Размер"
	return self


ExternalListMapManipulator InProcessorWithMessageGetPositionAndThenInvokeMethod <Processor> processor <ListMap> message <List> positionUID <Method> method
	actor = processor ContextActor
	job = entitiesFactory CreateEmptyJob
	actor ActorSetJob job (self.machine GenerateUID)
	job JobSetProperty "Сообщение" message
	job JobSetProperty "Метод" method

	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простой строкой" self &ExternalListMapManipulator_PositionReceived job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простой строкой"
	request MessageSetReceiver positionUID
	processor SendMessage request

	return self

ExternalListMapManipulator PositionReceived <Processor> processor
	method = ((processor ContextJob) JobProperty "Метод") AsMethod
	method Invoke self processor (processor EntityFromMessageField "Значение простой строкой" "Значение") ((processor ContextJob) JobProperty "Сообщение")
	processor FinishThisJob
	return self


ExternalListMapManipulator AtInsertInternal <Processor> processor position <ListMap> message
	actor = processor ContextActor
	listMap = (actor ActorProperty "Отображение списков") AsList
	listOfActors = (actor ActorProperty "Список объектов") AsList

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetRequest (message MessageRequest)
	reply MessageSetReceiver (message MessageSender)
	if (listMap Size) < position
		reply MessageSetReplyFail
	else
		reply MessageSetReplySuccess
		value = listMap At position
		if listOfActors NotContains position
			value = ((self.machine ActorsFactory) CreateActorFromObject value)
		reply AtPut "Замещенное значение" value
		listMap AtPut position (message At "Объект")
		if (message At "Простой") IsNil
			listOfActors RemoveFirst position
		else
			listOfActors PushSorted position
	processor SendMessage reply
	return self

ExternalListMapManipulator AtInsert <Processor> processor
	message = processor MessageInMessageSlot "Добавить объект на позицию"
	self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message (message At "Позиция") &ExternalListMapManipulator_AtInsertInternal
	return self



ExternalListMapManipulator AtGetInternal <Processor> processor position <ListMap> message
	actor = processor ContextActor
	listMap = (actor ActorProperty "Отображение списков") AsList
	listOfActors = (actor ActorProperty "Список объектов") AsList

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetRequest (message MessageRequest)
	reply MessageSetReceiver (message MessageSender)
	if (listMap Size) <= position
		reply MessageSetReplyFail
	else
		reply MessageSetReplySuccess
		value = (listMap At position)
		if listOfActors NotContains position
			value = ((self.machine ActorsFactory) CreateActorFromObject value)
		reply AtPut "Объект" value
	processor SendMessage reply
	return self


ExternalListMapManipulator AtGet <Processor> processor
	message = processor MessageInMessageSlot "Послать сообщение объекту на позиции"
	self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message (message At "Позиция") &ExternalListMapManipulator_AtGetInternal
	return self


ExternalListMapManipulator AtSendInternal <Processor> processor position <ListMap> message
	actor = processor ContextActor
	listMap = (actor ActorProperty "Отображение списков") AsListMap
	listOfActors = (actor ActorProperty "Список объектов") AsList

	if (listMap Size) <= position
		reply = entitiesFactory CreateEmptyMessage
		reply MessageSetReplyFail
		reply MessageSetRequest (message MessageRequest)
		reply MessageSetReceiver (message MessageSender)
		processor SendMessage reply
	else
		value = (listMap At position)
		if listOfActors NotContains position
				value = ((self.machine ActorsFactory) CreateActorFromObject value)
		job = entitiesFactory CreateEmptyJob
		job JobSetProperty "Заказчик" (message MessageSender)
		job JobSetProperty "Имя ожидаемого сообщения" ((message ListMapAt "Сообщение") At "Запрос")
		(processor ContextActor) ActorSetJob (self.machine GenerateUID) job
		messageSlot = processor CreateStageReplyEntityBasicMethodInJob ((message ListMapAt "Сообщение") At "Запрос") self &ExternalListMapManipulator_AnswerReceived job
		messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" value)
		message = (message ListMapAt "Сообщение")
		message MessageSetReceiver value
		processor SendMessage message
	return self


ExternalListMapManipulator AnswerReceived <Processor> processor
	actor = processor ContextActor
	job = processor ContextJob
	receiver = job JobProperty "Заказчик"
	incapsulatedMessage = processor MessageInMessageSlot (job JobProperty "Имя ожидаемого сообщения")
	message = entitiesFactory CreateEmptyMessage
	message MessageSetTypeReply
	message MessageSetRequest "Послать сообщение объекту на позиции"
	message AtPut "Ответ" incapsulatedMessage
	message MessageSetReceiver receiver
	processor SendMessage message
	return self


ExternalListMapManipulator AtSend <Processor> processor
	message = processor MessageInMessageSlot "Послать сообщение объекту на позиции"
	self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message (message At "Позиция") &ExternalListMapManipulator_AtSendInternal
	return self

ExternalListMapManipulator SendToAll <Processor> processor
	request = processor MessageInMessageSlot "Послать всем объектам"
	messageToSend = request ListMapAt "Сообщение"
	actor = processor ContextActor
	listMap = (actor ActorProperty "Отображение списков") AsListMap
	listOfActors = (actor ActorProperty "Список объектов") AsList

	// Создание работы-обработчика ответов

	handler = entitiesFactory CreateEmptyJob
	handler JobSetProperty (listMap Size) "Осталось ответов"
	handler JobSetProperty request "Сообщение запроса"
	handler JobSetProperty "Всюду успех" "Ответ в общем"

	actionWithAnswers = (request ListAt "Действия с ответами")
	method = nil
	if actionWithAnswers == "Переотправить"
		method = &ExternalListMapManipulator_SendToAllResendAnswersHandler
	elif actionWithAnswers == "Ответить в общем"
		method = &ExternalListMapManipulator_SendToAllAnswerInCommonHandler
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob (messageToSend MessageRequest) self method handler


	actor ActorSetJob handler (self.machine GenerateUID)


	// Непосредственно посылка сообщений

	iteratorInListMap = listMap First
	while iteratorInListMap NotThisEnd
		receiver = nil
		if listOfActors Contains (iteratorInListMap ThisKey)
			receiver = iteratorInListMap ThisData
		else
			receiver = (self.machine ActorsFactory) CreateActorFromObject (iteratorInListMap ThisData)
		messageToSend2 = messageToSend DeepClone
		messageToSend2 MessageSetReceiver receiver
		processor SendMessage messageToSend2

		iteratorInListMap ++
	return self


ExternalListMapManipulator SendToAllResendAnswersHandler <Processor> processor
	actor = processor ContextActor
	job = processor ContextJob
	answersRemained = (job JobProperty "Осталось ответов") AsNumber
	request = (job JobProperty "Сообщение запроса") AsListMap
	receiver = request MessageSender

	incapsulatedMessage = (processor MessageInMessageSlot ((request ListMapAt "Сообщение") MessageRequest))
	message = entitiesFactory CreateEmptyMessage
	message MessageSetReceiver receiver
	message MessageSetTypeNotification
	message MessageSetRequest (request MessageRequest)
	message AtPut "Ответ" incapsulatedMessage
	processor SendMessage message

	answersRemained --
	if incapsulatedMessage MessageAnswerIsFail
		job JobSetProperty "Неудача" "Ответ в общем"

	if answersRemained == 0
		summaryAnswer = request TempDeepClone
		summaryAnswer MessageSetTypeReply
		summaryAnswer MessageSetAnswerSuccess
		summaryAnswer AtPut "Отчет" (job JobProperty "Ответ в общем")
		summaryAnswer MessageSetReceiver receiver
		processor SendMessage summaryAnswer
		processor FinishThisJob
	return self


ExternalListMapManipulator SendToAllAnswerInCommonHandler <Processor> processor
	actor = processor ContextActor
	job = processor ContextJob
	answersRemained = (job JobProperty "Осталось ответов") AsNumber
	request = (job JobProperty "Сообщение запроса") AsListMap
	receiver = request MessageSender

	answersRemained --

	if (processor MessageInMessageSlot ((request ListMapAt "Сообщение") MessageRequest)) MessageAnswerIsFail
		job JobSetProperty "Неудача" "Ответ в общем"

	if answersRemained == 0
		summaryAnswer = request TempDeepClone
		summaryAnswer MessageSetTypeReply
		summaryAnswer MessageSetAnswerSuccess
		summaryAnswer AtPut "Отчет" (job JobProperty "Ответ в общем")
		summaryAnswer MessageSetReceiver receiver
		processor SendMessage summaryAnswer
		processor FinishThisJob
	return self
