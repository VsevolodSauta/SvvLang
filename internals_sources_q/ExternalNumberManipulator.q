<ExternalNumberManipulator@Object> <Machine> machine

ExternalNumberManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalNumberManipulator <List> CreateUIDNumberFromUIDActor <List> uid
	job = entitiesFactory CreateEmptyJob

	// Обеспечение внутреннего протокола
	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_SimpleNumber job
	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Значение простой строкой" self &ExternalNumberManipulator_SimpleString job


	// Создание арифметических операций
	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "+=" self &ExternalNumberManipulator_AddInPlace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "-=" self &ExternalNumberManipulator_SubInPlace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "*=" self &ExternalNumberManipulator_MulInPlace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "/=" self &ExternalNumberManipulator_DivInPlace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "%=" self &ExternalNumberManipulator_ModInPlace job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "++" self &ExternalNumberManipulator_Increment job

	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "--" self &ExternalNumberManipulator_Decrement job


	// Создание набора функций
	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Модуль" self &ExternalNumberManipulator_Absolute job


	// Создание оповещения.
	messageSlot = self.machine.fakeProcessor CreateStageRequestEntityBasicMethodInJob "Оповестить" self &ExternalNumberManipulator_NotifyRequest job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Условие")

	// Создание слота получения оповещения.
	messageSlot = self.machine.fakeProcessor CreateStageEmptyEntityBasicMethodInJob "Текущее значение получено" self &ExternalNumberManipulator_CurrentValueReceived job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Текущее значение")

	actor = self.machine ActorByUID uid
	actor ActorSetJob job "Основная работа числа"
	return uid


ExternalNumberManipulator SimpleNumber <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	message = entitiesFactory CreateEmptyMessage
	message MessageSetAnswerSuccess
	message AtPut "Значение" ((number Clone) Autorelease)
	processor SendReplyForMessage message "Значение простым числом"
	return self


ExternalNumberManipulator SimpleString <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	message = entitiesFactory CreateEmptyMessage
	message MessageSetAnswerSuccess
	message AtPut "Значение" (stringFactory FromNumber number)
	processor SendReplyForMessage message "Значение простой строкой"
	return self


ExternalNumberManipulator AddInPlace <Processor> processor
	actor = processor ContextActor
	requestArgument = processor EntityFromNamedMessageField "+=" "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	processor DefineFieldInNameSpaceWithUID "Заказчик" (jobToProcessThisEvent JobFields) (processor EntityFromNamedMessageField "+=" "Отправитель")
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_AddInPlaceSimple jobToProcessThisEvent
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" requestArgument)
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	processor AddJobWithName jobToProcessThisEvent (self.machine GenerateUID)

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver requestArgument
	processor SendMessage request
	return self

ExternalNumberManipulator AddInPlaceSimple <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number += (processor EntityFromNamedMessageField "Значение простым числом" "Значение")

	receiver = processor FieldNameToUID "Заказчик"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "+="
	reply MessageSetReceiver receiver
	processor SendMessage reply

	self CheckForNotifications processor
	return self


ExternalNumberManipulator SubInPlace <Processor> processor
	actor = processor ContextActor
	requestArgument = processor EntityFromNamedMessageField "-=" "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	processor DefineFieldInNameSpaceWithUID "Заказчик" (jobToProcessThisEvent JobFields) (processor EntityFromNamedMessageField "-=" "Отправитель")
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_SubInPlaceSimple jobToProcessThisEvent
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" requestArgument)
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	processor AddJobWithName jobToProcessThisEvent (self.machine GenerateUID)

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver requestArgument
	processor SendMessage request
	return self

ExternalNumberManipulator SubInPlaceSimple <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number -= (processor EntityFromNamedMessageField "Значение простым числом" "Значение")

	receiver = processor FieldNameToUID "Заказчик"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "-="
	reply MessageSetReceiver receiver
	processor SendMessage reply

	self CheckForNotifications processor
	return self


ExternalNumberManipulator MulInPlace <Processor> processor
	actor = processor ContextActor
	requestArgument = processor EntityFromNamedMessageField "*=" "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	processor DefineFieldInNameSpaceWithUID "Заказчик" (jobToProcessThisEvent JobFields) (processor EntityFromNamedMessageField "*=" "Отправитель")
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_MulInPlaceSimple jobToProcessThisEvent
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" requestArgument)
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	processor AddJobWithName jobToProcessThisEvent (self.machine GenerateUID)

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver requestArgument
	processor SendMessage request
	return self

ExternalNumberManipulator MulInPlaceSimple <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number *= (processor EntityFromNamedMessageField "Значение простым числом" "Значение")

	receiver = processor FieldNameToUID "Заказчик"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "*="
	reply MessageSetReceiver receiver
	processor SendMessage reply

	self CheckForNotifications processor
	return self


ExternalNumberManipulator DivInPlace <Processor> processor
	actor = processor ContextActor
	requestArgument = processor EntityFromNamedMessageField "/=" "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	processor DefineFieldInNameSpaceWithUID "Заказчик" (jobToProcessThisEvent JobFields) (processor EntityFromNamedMessageField "/=" "Отправитель")
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_DivInPlaceSimple jobToProcessThisEvent
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" requestArgument)
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	processor AddJobWithName jobToProcessThisEvent (self.machine GenerateUID)

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver requestArgument
	processor SendMessage request
	return self

ExternalNumberManipulator DivInPlaceSimple <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number /= (processor EntityFromNamedMessageField "Значение простым числом" "Значение")

	receiver = processor FieldNameToUID "Заказчик"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "/="
	reply MessageSetReceiver receiver
	processor SendMessage reply

	self CheckForNotifications processor
	return self


ExternalNumberManipulator ModInPlace <Processor> processor
	actor = processor ContextActor
	requestArgument = processor EntityFromNamedMessageField "%=" "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	processor DefineFieldInNameSpaceWithUID "Заказчик" (jobToProcessThisEvent JobFields) (processor EntityFromNamedMessageField "%=" "Отправитель")
	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простым числом" self &ExternalNumberManipulator_ModInPlaceSimple jobToProcessThisEvent
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Отправитель" requestArgument)
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionEquality "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	processor AddJobWithName jobToProcessThisEvent (self.machine GenerateUID)

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простым числом"
	request MessageSetReceiver requestArgument
	processor SendMessage request
	return self

ExternalNumberManipulator ModInPlaceSimple <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number %= (processor EntityFromNamedMessageField "Значение простым числом" "Значение")

	receiver = processor FieldNameToUID "Заказчик"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "%="
	reply MessageSetReceiver receiver
	processor SendMessage reply

	self CheckForNotifications processor
	return self


ExternalNumberManipulator Increment <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number ++

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "++"

	self CheckForNotifications processor
	return self


ExternalNumberManipulator Decrement <Processor> processor
	actor = processor ContextActor
	number = (actor ActorProperty "Число") AsNumber
	number --

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "--"

	self CheckForNotifications processor
	return self


ExternalNumberManipulator Absolute <Processor> processor
	actor = processor ContextActor
	number = ((actor ActorProperty "Число") AsNumber) Abs

	cloneUID = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine (processor ContextActorUID)
	clone = self.machine UIDToActor cloneUID

	(clone ActorProperties) AtPut "Число" number

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply AtPut "Значение" cloneUID
	processor SendReplyForMessage reply "Модуль"
	return self

ExternalNumberManipulator NotifyRequest <Processor> processor
	actor = processor ContextActor
	request = (processor MessageInMessageSlot "Оповестить")

	if (actor ActorProperties) NotContainsKey "Значения при оповещении"
		actor ActorSetProperty (entitiesFactory CreateEmptyListMap) "Значения при оповещении"

	actor ActorAddNotificationRequest request

	if (request At "Значение") != nil
		msg = entitiesFactory CreateEmptyMessage
		msg MessageSetReceiver (request At "Значение")
		msg MessageSetTypeRequest
		msg MessageSetRequest "Оповестить"
		msg AtPut "Условие" "Значение изменилось"
		processor SendMessage msg

	self CheckForNotifications processor

	reply = (request DeepClone) Autorelease
	reply MessageSetTypeReply
	reply MessageSetReplySuccess
	reply AtPut "Текущее значение" (actor ActorProperty "Число")
	reply MessageSetReceiver (request MessageSender)
	processor SendMessage reply

	return self

ExternalNumberManipulator CurrentValueReceived <Processor> processor
	actor = processor ContextActor
	receivedMessage = processor MessageInMessageSlot "Текущее значение получено"
	((actor ActorProperty "Значения при оповещении") AsListMap) AtPut (receivedMessage MessageSender) (receivedMessage NumberAt "Текущее значение")

	if (receivedMessage MessageType) == "Оповещение"
		request = (receivedMessage DeepClone) Autorelease
		request MessageSetTypeRequest
		request MessageSetRequest "Оповестить"
		request MessageSetReceiver (receivedMessage MessageSender)
		processor SendMessage request

	// Мониторится состояние объектов БЕСКОНЕЧНО

	self CheckForNotifications processor
	return self

ExternalNumberManipulator CheckForNotifications <Processor> processor
	actor = processor ContextActor
	notifications = actor ActorNotificationRequests
	currentValue = (actor ActorProperty "Число") AsNumber
	prevValue = (actor ActorProperty "Число (предыдущее значение)") AsNumber

	notificationsIterator = notifications First
	while notificationsIterator NotThisEnd
		request = notificationsIterator ListMapData
		condition = request At "Условие"
		value = request At "Значение"
		valuesValue = nil
		if value != nil
			valuesValue = ((actor ActorProperty "Значения при оповещении") AsListMap) At value
			if valuesValue == nil
				notificationsIterator ++
				continue
		shouldNotify = false
		if (condition == ">")
			if (currentValue > valuesValue)
				shouldNotify = true
		elif (condition == "<")
			if (currentValue < valuesValue)
				shouldNotify = true
		elif ((condition == "=") Or (condition == "=="))
			if (currentValue == valuesValue)
				shouldNotify = true
		elif (condition == "Значение изменилось")
			if (currentValue != prevValue)
				shouldNotify = true
		else
			console PrintString "Некорректное условие на оповещение: "
			console PrintLnString condition
			// notificationsIterator Remove
			notificationsIterator --
		if shouldNotify
			notifyMessage = entitiesFactory CreateEmptyMessage
			notifyMessage MessageSetTypeNotification
			notifyMessage AtPut "Условие" condition
			if value != nil
				notifyMessage AtPut "Значение" value
			notifyMessage AtPut "Текущее значение" currentValue
			notifyMessage MessageSetReceiver (request MessageSender)
			processor SendMessage notifyMessage
			notificationsIterator Remove
		notificationsIterator ++
	actor ActorSetProperty ((currentValue Clone) Autorelease) "Число (предыдущее значение)"
	return self
