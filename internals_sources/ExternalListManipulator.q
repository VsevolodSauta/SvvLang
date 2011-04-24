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

ExternalListManipulator <List> CreateUIDListFromUIDObject <List> uid
	job = entitiesFactory CreateEmptyJob

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Создать список с целыми числами на интервале" self &ExternalListManipulator_ListWithIntegersInInterval job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Левая граница")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Правая граница")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Послать всем элементам" self &ExternalListManipulator_SendToAll job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Сообщение")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Действия с ответами")

	object = self.machine ObjectByUID uid
	object ObjectSetJob job "Основная работа списка"
	return uid


ExternalListManipulator ListWithIntegersInIntervalHandler <Processor> processor
	leftAnswer = processor MessageInMessageSlot "Ожидаемое сообщение от левой границы"
	rightAnswer = processor MessageInMessageSlot "Ожидаемое сообщение от правой границы"

	// Не хватает округления границ !

	list = entitiesFactory CreateEmptyList
	cur = (leftAnswer NumberAt "Число") + 1
	right = (rightAnswer NumberAt "Число")
	while cur < right
		list Append (cur TempClone)
		cur ++

	uid = objectsFactory CreateList list
	reply = (((processor ContextJob) JobProperty "Сообщение заказа") AsListMap) TempDeepClone
	reply MessageSetTypeReply
	reply MessageSetReplySuccess
	reply MessageSetReceiver (reply MessageSender)
	reply AtPut "Список" uid
	processor SendMessage reply

	processor FinishThisJob
	return self


ExternalListManipulator ListWithIntegersInInterval <Processor> processor
	request = processor MessageInMessageSlot "Создать список с целыми числами на интервале"
	object = processor ContextObject

	leftElement = request At "Левая граница"
	rightElement = request At "Правая граница"

	handler = entitiesFactory CreateEmptyJob
	handlerName = (self.machine GenerateUID)
	object ObjectSetJob handler handlerName

	stage = entitiesFactory CreateEmptyJobStage
	stage StageSetMethod "Единственный метод"
	handler JobSetStage stage "Единственная стадия"

	messageSlotForLeft = entitiesFactory CreateEmptyMessageSlot
	messageSlotForLeft MessageSlotSetCondition (entitiesFactory CreateConditionEqualityWithField "Отправитель" "Левая граница")
	messageSlotForLeft MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Число")
	handler JobSetMessageSlot messageSlotForLeft "Ожидаемое сообщение от левой границы"
	processor AttachToStageMessageSlotInJob "Единственная стадия" "Ожидаемое сообщение от левой границы" handlerName

	messageSlotForRight = entitiesFactory CreateEmptyMessageSlot
	messageSlotForRight MessageSlotSetCondition (entitiesFactory CreateConditionEqualityWithField "Отправитель" "Правая граница")
	messageSlotForRight MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Число")
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
	msg = msg TempDeepClone
	msg MessageSetReceiver rightElement
	processor SendMessage msg

	return self


ExternalListManipulator SendToAllRedirectAnswersHandler <Processor> processor
	object = processor ContextObject
	job = processor ContextJob
	answersRemained = (job JobProperty "Осталось ответов") AsNumber
	request = (job JobProperty "Сообщение запроса") AsListMap
	receiver = request MessageSender

	msgToRedirect = (processor MessageInMessageSlot ((request ListMapAt "Сообщение") MessageRequest)) TempDeepClone
	msgToRedirect MessageSetReceiver receiver
	msgToRedirect AtPut "Исходный отправитель" (msgToRedirect MessageSender)
	processor SendMessage msgToRedirect

	answersRemained --
	if msgToRedirect MessageAnswerIsFail
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


ExternalListManipulator SendToAllAnswerInCommonHandler <Processor> processor
	object = processor ContextObject
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


ExternalListManipulator SendToAll <Processor> processor
	request = processor MessageInMessageSlot "Послать всем элементам"
	messageToSend = request ListMapAt "Сообщение"
	object = processor ContextObject

	// Создание работы-обработчика ответов

	handler = entitiesFactory CreateEmptyJob
	actionWithAnswers = (processor EntityFromNamedMessageField "Послать всем элементам" "Действия с ответами")
	method = nil
	if actionWithAnswers == "Перенаправить"
		method = &ExternalListManipulator_SendToAllRedirectAnswersHandler
	elif actionWithAnswers == "Ответить в общем"
		method = &ExternalListManipulator_SendToAllAnswerInCommonHandler
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob (messageToSend MessageRequest) self method handler


	// Очень плохая практика!!!

	object ObjectSetJob handler (self.machine GenerateUID)


	// Непосредственно посылка сообщений

	list = (object ObjectProperty "Список") AsList
	listOfObjects = (object ObjectProperty "Список объектов") AsList
	iteratorInList = list First
	iteratorInListOfObjects = listOfObjects First
	position = 0
	while iteratorInList NotThisEnd
		data = iteratorInList ThisData
		flag = true
		receiver = nil
		if iteratorInListOfObjects NotThisEnd
			if position == (iteratorInListOfObjects NumberData)
				flag = false
				receiver = data
				iteratorInListOfObjects ++
		if flag
			receiver = objectsFactory CreateValue data
		messageToSend2 = messageToSend TempDeepClone
		messageToSend2 MessageSetReceiver receiver
		processor SendMessage messageToSend2

		iteratorInList ++
		position ++

	handler JobSetProperty position "Осталось ответов"
	handler JobSetProperty request "Сообщение запроса"
	handler JobSetProperty "Всюду успех" "Ответ в общем"

	// Ответ заказчику

	// message = entitiesFactory CreateEmptyMessage
	// message MessageSetReceiver (request MessageSender)
	// message MessageSetTypeReply
	// message MessageSetReplySuccess
	// message MessageSetRequest "Послать всем элементам"
	// processor SendMessage message
	return self
