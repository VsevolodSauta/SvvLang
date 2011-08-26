<ExternalListManipulator> <Machine> machine

ExternalListManipulator Init
	return self

ExternalListManipulator Clone
	return self Retain

ExternalListManipulator DeepClone
	return self Retain

ExternalListManipulator Destroy
	return self Destroy

ExternalListManipulator Compare <ExternalListManipulator> manipulator
	return equal

ExternalListManipulator SetMachine <Machine> machine
	self.machine = machine
	return self


ExternalListManipulator <List> CreateUIDListFromUIDActor <List> uid
	job = entitiesFactory CreateEmptyJob

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Создать список с целыми числами на интервале" self &ExternalListManipulator_ListWithIntegersInInterval job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Левая граница")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Правая граница")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Послать всем объектам" self &ExternalListManipulator_SendToAll job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Сообщение")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Действия с ответами")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Объект на позиции" self &ExternalListManipulator_AtGet job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Послать сообщение объекту на позиции" self &ExternalListManipulator_AtSend job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Заменить объект на позиции" self &ExternalListManipulator_AtReplace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Объект")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Добавить объект на позицию" self &ExternalListManipulator_AtInsert job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Позиция")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Объект")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Размер" self &ExternalListManipulator_Size job

	actor = self.machine ActorByUID uid
	actor ActorSetJob job "Основная работа списка"
	return uid


ExternalListManipulator ListWithIntegersInIntervalHandler <Processor> processor
	leftAnswer = processor MessageInMessageSlot "Ожидаемое сообщение от левой границы"
	rightAnswer = processor MessageInMessageSlot "Ожидаемое сообщение от правой границы"

	// Не хватает округления границ !

	list = entitiesFactory CreateEmptyList
	cur = (leftAnswer NumberAt "Значение") + 1
	right = (rightAnswer NumberAt "Значение")
	while cur < right
		list Append ((cur Clone) Autorelease)
		cur ++

	uid = (self.machine ActorsFactory) CreateList list
	reply = ((((processor ContextJob) JobProperty "Сообщение заказа") AsListMap) DeepClone) Autorelease
	reply MessageSetTypeReply
	reply MessageSetReplySuccess
	reply MessageSetReceiver (reply MessageSender)
	reply AtPut "Список" uid
	processor SendMessage reply

	processor FinishThisJob
	return self


ExternalListManipulator ListWithIntegersInInterval <Processor> processor
	request = processor MessageInMessageSlot "Создать список с целыми числами на интервале"
	actor = processor ContextActor

	leftElement = request At "Левая граница"
	rightElement = request At "Правая граница"

	handler = entitiesFactory CreateEmptyJob
	handlerName = (self.machine GenerateUID)
	actor ActorSetJob handler handlerName

	stage = entitiesFactory CreateEmptyJobStage
	stage StageSetMethod "Единственный метод"
	handler JobSetStage stage "Единственная стадия"

	messageSlotForLeft = entitiesFactory CreateEmptyMessageSlot
	messageSlotForLeft MessageSlotSetCondition (entitiesFactory CreateConditionEqualityWithField "Отправитель" "Левая граница")
	messageSlotForLeft MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	handler JobSetMessageSlot messageSlotForLeft "Ожидаемое сообщение от левой границы"
	processor AttachToStageMessageSlotInJob "Единственная стадия" "Ожидаемое сообщение от левой границы" handlerName

	messageSlotForRight = entitiesFactory CreateEmptyMessageSlot
	messageSlotForRight MessageSlotSetCondition (entitiesFactory CreateConditionEqualityWithField "Отправитель" "Правая граница")
	messageSlotForRight MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	handler JobSetMessageSlot messageSlotForRight "Ожидаемое сообщение от правой границы"
	processor AttachToStageMessageSlotInJob "Единственная стадия" "Ожидаемое сообщение от правой границы" handlerName

	handler JobSetBasicMethod self &ExternalListManipulator_ListWithIntegersInIntervalHandler "Единственный метод"

	handler JobSetProperty request "Сообщение заказа"
	processor DefineFieldInNameSpaceWithUID "Левая граница" (handler JobFields) leftElement
	processor DefineFieldInNameSpaceWithUID "Правая граница" (handler JobFields) rightElement

	msg = entitiesFactory CreateEmptyMessage
	msg MessageSetTypeRequest
	msg MessageSetRequest "Значение простым числом"
	msg MessageSetReceiver leftElement
	processor SendMessage msg
	msg = (msg DeepClone) Autorelease
	msg MessageSetReceiver rightElement
	processor SendMessage msg

	return self


ExternalListManipulator SendToAllResendAnswersHandler <Processor> processor
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
		summaryAnswer = (request DeepClone) Autorelease
		summaryAnswer MessageSetTypeReply
		summaryAnswer MessageSetAnswerSuccess
		summaryAnswer AtPut "Отчет" (job JobProperty "Ответ в общем")
		summaryAnswer MessageSetReceiver receiver
		processor SendMessage summaryAnswer
		processor FinishThisJob
	return self


ExternalListManipulator SendToAllAnswerInCommonHandler <Processor> processor
	actor = processor ContextActor
	job = processor ContextJob
	answersRemained = (job JobProperty "Осталось ответов") AsNumber
	request = (job JobProperty "Сообщение запроса") AsListMap
	receiver = request MessageSender

	answersRemained --

	if (processor MessageInMessageSlot ((request ListMapAt "Сообщение") MessageRequest)) MessageAnswerIsFail
		job JobSetProperty "Неудача" "Ответ в общем"

	if answersRemained == 0
		summaryAnswer = (request DeepClone) Autorelease
		summaryAnswer MessageSetTypeReply
		summaryAnswer MessageSetAnswerSuccess
		summaryAnswer AtPut "Отчет" (job JobProperty "Ответ в общем")
		summaryAnswer MessageSetReceiver receiver
		processor SendMessage summaryAnswer
		processor FinishThisJob
	return self


ExternalListManipulator SendToAll <Processor> processor
	request = processor MessageInMessageSlot "Послать всем объектам"
	messageToSend = request ListMapAt "Сообщение"
	actor = processor ContextActor

	// Создание работы-обработчика ответов

	handler = entitiesFactory CreateEmptyJob
	actionWithAnswers = (request ListAt "Действия с ответами")
	method = nil
	if actionWithAnswers == "Переотправить"
		method = &ExternalListManipulator_SendToAllResendAnswersHandler
	elif actionWithAnswers == "Ответить в общем"
		method = &ExternalListManipulator_SendToAllAnswerInCommonHandler
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob (messageToSend MessageRequest) self method handler


	actor ActorSetJob handler (self.machine GenerateUID)


	// Непосредственно посылка сообщений

	list = (actor ActorProperty "Список") AsList
	listOfActors = (actor ActorProperty "Список объектов") AsList
	iteratorInList = list First
	iteratorInListOfActors = listOfActors First
	position = 0
	while iteratorInList NotThisEnd
		data = iteratorInList ThisData
		flag = true
		receiver = nil
		if iteratorInListOfActors NotThisEnd
			if position == (iteratorInListOfActors NumberData)
				flag = false
				receiver = data
				iteratorInListOfActors ++
		if flag
			receiver = (self.machine ActorsFactory) CreateActorFromObject data
		messageToSend2 = (messageToSend DeepClone) Autorelease
		messageToSend2 MessageSetReceiver receiver
		processor SendMessage messageToSend2

		iteratorInList ++
		position ++

	handler JobSetProperty position "Осталось ответов"
	handler JobSetProperty request "Сообщение запроса"
	handler JobSetProperty "Всюду успех" "Ответ в общем"
	return self


ExternalListManipulator InProcessorWithMessageGetPositionAndThenInvokeMethod <Processor> processor <ListMap> message <List> positionUID <Method> method
	actor = processor ContextActor
	job = entitiesFactory CreateEmptyJob
	actor ActorSetJob job (self.machine GenerateUID)
	job JobSetProperty "Сообщение" message
	job JobSetProperty "Метод" method

	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalListManipulator_PositionReceived job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver positionUID
	processor SendMessage request

	return self

ExternalListManipulator PositionReceived <Processor> processor
	method = ((processor ContextJob) JobProperty "Метод") AsMethod
	method Invoke self processor (processor EntityFromMessageField "Значение простым числом" "Значение") ((processor ContextJob) JobProperty "Сообщение")
	processor FinishThisJob
	return self

ExternalListManipulator AtGetInternal <Processor> processor position <ListMap> message
	if position TypeIsNumber
		actor = processor ContextActor
		list = (actor ActorProperty "Список") AsList
		listOfActors = (actor ActorProperty "Список объектов") AsList

		reply = entitiesFactory CreateEmptyMessage
		reply MessageSetRequest (message MessageRequest)
		reply MessageSetReceiver (message MessageSender)
		if (list Size) <= position
			reply MessageSetReplyFail
		else
			reply MessageSetReplySuccess
			value = (list At position)
			if listOfActors NotContains position
				value = ((self.machine ActorsFactory) CreateActorFromObject value)
			reply AtPut "Объект" value
		processor SendMessage reply
	else
		self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message position &ExternalListManipulator_AtGetInternal
	return self



ExternalListManipulator AtGet <Processor> processor
	message = processor MessageInMessageSlot "Объект на позиции"
	self AtGetInternal processor (message At "Позиция") message
	return self


ExternalListManipulator AtInsertInternal <Processor> processor position <ListMap> message
	if position TypeIsNumber
		actor = processor ContextActor
		list = (actor ActorProperty "Список") AsList
		listOfActors = (actor ActorProperty "Список объектов") AsList

		reply = entitiesFactory CreateEmptyMessage
		reply MessageSetRequest (message MessageRequest)
		reply MessageSetReceiver (message MessageSender)
		if (list Size) < position
			reply MessageSetReplyFail
		else
			reply MessageSetReplySuccess
			iterator = listOfActors First
			while iterator NotThisEnd
				if (iterator NumberData) >= position
					(iterator NumberData) ++
				iterator ++
			list AtInsert position (message At "Объект")
			if (message At "Простой") NotIs nil
				listOfActors PushSorted position
		processor SendMessage reply
	else
		self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message position &ExternalListManipulator_AtInsertInternal
	return self


ExternalListManipulator AtInsert <Processor> processor
	message = processor MessageInMessageSlot "Добавить объект на позицию"
	self AtInsertInternal processor (message At "Позиция") message
	return self


ExternalListManipulator AtReplaceInternal <Processor> processor position <ListMap> message
	if position TypeIsNumber
		actor = processor ContextActor
		list = (actor ActorProperty "Список") AsList
		listOfActors = (actor ActorProperty "Список объектов") AsList

		reply = entitiesFactory CreateEmptyMessage
		reply MessageSetRequest (message MessageRequest)
		reply MessageSetReceiver (message MessageSender)
		if (list Size) <= position
			reply MessageSetReplyFail
		else
			reply MessageSetReplySuccess
			value = (list At position)
			if listOfActors NotContains position
				value = ((self.machine ActorsFactory) CreateActorFromObject value)
			reply AtPut "Замещенный объект" value
			list AtPut position (message At "Объект")
			if (message At "Простой") Is nil
				listOfActors RemoveFirst position
			else
				listOfActors PushSorted position
		processor SendMessage reply
	else
		self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message position &ExternalListManipulator_AtReplaceInternal
	return self


ExternalListManipulator AtReplace <Processor> processor
	message = processor MessageInMessageSlot "Заменить объект на позиции"
	self AtReplaceInternal processor (message At "Позиция") message
	return self


ExternalListManipulator AtSendInternal <Processor> processor position <ListMap> message
	if position TypeIsNumber
		actor = processor ContextActor
		list = (actor ActorProperty "Список") AsList
		listOfActors = (actor ActorProperty "Список объектов") AsList

		if (list Size) <= position
			reply = entitiesFactory CreateEmptyMessage
			reply MessageSetReplyFail
			reply MessageSetRequest (message MessageRequest)
			reply MessageSetReceiver (message MessageSender)
			processor SendMessage reply
		else
			value = (list At position)
			if listOfActors NotContains position
				value = ((self.machine ActorsFactory) CreateActorFromObject value)
			job = entitiesFactory CreateEmptyJob
			job JobSetProperty "Заказчик" (message MessageSender)
			job JobSetProperty "Имя ожидаемого сообщения" ((message ListMapAt "Сообщение") At "Запрос")
			(processor ContextActor) ActorSetJob (self.machine GenerateUID) job
			messageSlot = processor CreateStageReplyEntityBasicMethodInJob ((message ListMapAt "Сообщение") At "Запрос") self &ExternalListManipulator_AnswerReceived job
			messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" value)
			message = (message ListMapAt "Сообщение")
			message MessageSetReceiver value
		processor SendMessage message
	else
		self InProcessorWithMessageGetPositionAndThenInvokeMethod processor message position &ExternalListManipulator_AtSendInternal
	return self

ExternalListManipulator AnswerReceived <Processor> processor
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


ExternalListManipulator AtSend <Processor> processor
	message = processor MessageInMessageSlot "Послать сообщение объекту на позиции"
	self AtSendInternal processor (message At "Позиция") message
	return self

ExternalListManipulator Size <Processor> processor
	message = entitiesFactory CreateEmptyMessage
	message AtPut "Размер" ((self.machine ActorsFactory) CreateActorFromObject ((((processor ContextActor) ActorProperty "Список") AsList) Size))
	processor SendReplyForMessage message "Размер"
	return self
