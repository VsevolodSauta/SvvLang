<ExternalNumberManipulator> <Machine> machine

ExternalNumberManipulator Init
	return self

ExternalNumberManipulator Clone
	return self Retain

ExternalNumberManipulator DeepClone
	return self Retain

ExternalNumberManipulator Destroy
	return self Destroy

ExternalNumberManipulator Compare <ExternalNumberManipulator> manipulator
	return equal

ExternalNumberManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalNumberManipulator <List> CreateUIDNumberFromUIDObject <List> uid
	job = entitiesFactory CreateEmptyJob
	
	// Обеспечение внутреннего протокола
	messageSlot = entitiesFactory CreateRequestMessageSlot "Значение простым числом"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Значение простым числом" "Значение простым числом" "Значение простым числом" messageSlot	

	messageSlot = entitiesFactory CreateRequestMessageSlot "Значение простой строкой"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Значение простой строкой" "Значение простой строкой" "Значение простой строкой" messageSlot
	
	// Создание арифметических операций
	messageSlot = entitiesFactory CreateRequestMessageSlot "+="
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "+=" "+=" "+=" messageSlot
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "-="
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "-=" "-=" "-=" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "*="
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "*=" "*=" "*=" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "/="
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "/=" "/=" "/=" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "/="
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Аргумент")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "/=" "/=" "/=" messageSlot
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "Инкремент"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Инкремент" "Инкремент" "Инкремент" messageSlot
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "Декремент"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Декремент" "Декремент" "Декремент" messageSlot
	
	// Создание набора функций
	messageSlot = entitiesFactory CreateRequestMessageSlot "Модуль"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Модуль" "Модуль" "Модуль" messageSlot
	
	
	// Создание оповещения.
	messageSlot = entitiesFactory CreateRequestMessageSlot "Оповестить"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Условие")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Значение")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Оповестить" "Опвестить" "Оповестить" messageSlot
	

	object = self.machine ObjectByUID uid
	object ObjectSetJob job
	return uid
	
	
ExternalNumberManipulator SimpleNumber <Processor> processor
	object = processor ContextObject
	number = object ObjectProperty "Число"
	message = entitiesFactory CreateEmptyMessage
	message MessageSetAnswerSuccess
	message AtPut "Число" (number TempClone)
	processor SendReplyForMessage message "Значение простым числом"
	return self
	

ExternalNumberManipulator SimpleString <Processor> processor
	object = processor ContextObject
	number = object ObjectProperty "Число"
	message = entitiesFactory CreateEmptyMessage
	message MessageSetAnswerSuccess
	message AtPut "Строка" (stringFactory FromNumber number)
	processor SendReplyForMessage message "Значение простой строкой"
	return self


ExternalNumberManipulator AddInPlace <Processor> processor
	object = processor ContextObject
	request = (processor ContextJob) JobMessageInMessageSlot "+="
	requestArgument = request ListAt "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	self.machine DefineFieldHelper (request MessageSender) "Перед кем отчетность" (jobToProcessThisEvent JobFields)
	name = requestArgument TempClone
	name Concatenate "Запрос для +="
	messageSlot = entitiesFactory CreateReplyMessageSlot "Значение простым числом"
	jobToProcessThisEvent JobCreateStageWithNameMethodMessageSlotNameAndEntity name name name messageSlot
	object ObjectSetBasicMethod self &AddInPlaceSimple name
	
	request2 = entitiesFactory CreateEmptyMessage
	request2 MessageSetTypeRequest
	request2 MessageSetRequest "Значение простым числом"
	request2 MessageSetReceiver requestArgument
	processor SendMessage request2
	return self

ExternalNumberManipulator AddInPlaceSimple <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	job = (processor ContextJob)
	request = job JobMessageInMessageSlot "Значение простым числом"
	number += (request NumberAt "Число")
	
	receiver = job JobFieldUIDWithName "Перед кем отчетность"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "+="
	processor SendMessage reply
	return self

	
ExternalNumberManipulator SubInPlace <Processor> processor
	object = processor ContextObject
	request = (processor ContextJob) JobMessageInMessageSlot "-="
	requestArgument = request ListAt "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	self.machine DefineFieldHelper (request MessageSender) "Перед кем отчетность" (jobToProcessThisEvent JobFields)
	name = requestArgument TempClone
	name Concatenate "Запрос для -="
	messageSlot = entitiesFactory CreateReplyMessageSlot "Значение простым числом"
	jobToProcessThisEvent JobCreateStageWithNameMethodMessageSlotNameAndEntity name name name messageSlot
	object ObjectSetBasicMethod self &SubInPlaceSimple name
	
	request2 = entitiesFactory CreateEmptyMessage
	request2 MessageSetTypeRequest
	request2 MessageSetRequest "Значение простым числом"
	request2 MessageSetReceiver requestArgument
	processor SendMessage request2
	return self

ExternalNumberManipulator SubInPlaceSimple <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	job = (processor ContextJob)
	request = job JobMessageInMessageSlot "Значение простым числом"
	number -= (request NumberAt "Число")
	
	receiver = job JobFieldUIDWithName "Перед кем отчетность"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "-="
	processor SendMessage reply
	return self

	
ExternalNumberManipulator MulInPlace <Processor> processor
	object = processor ContextObject
	request = (processor ContextJob) JobMessageInMessageSlot "*="
	requestArgument = request ListAt "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	self.machine DefineFieldHelper (request MessageSender) "Перед кем отчетность" (jobToProcessThisEvent JobFields)
	name = requestArgument TempClone
	name Concatenate "Запрос для *="
	messageSlot = entitiesFactory CreateReplyMessageSlot "Значение простым числом"
	jobToProcessThisEvent JobCreateStageWithNameMethodMessageSlotNameAndEntity name name name messageSlot
	object ObjectSetBasicMethod self &MulInPlaceSimple name
	
	request2 = entitiesFactory CreateEmptyMessage
	request2 MessageSetTypeRequest
	request2 MessageSetRequest "Значение простым числом"
	request2 MessageSetReceiver requestArgument
	processor SendMessage request2
	return self

ExternalNumberManipulator MulInPlaceSimple <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	job = (processor ContextJob)
	request = job JobMessageInMessageSlot "Значение простым числом"
	number *= (request NumberAt "Число")
	
	receiver = job JobFieldUIDWithName "Перед кем отчетность"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "*="
	processor SendMessage reply
	return self

	
ExternalNumberManipulator DivInPlace <Processor> processor
	object = processor ContextObject
	request = (processor ContextJob) JobMessageInMessageSlot "/="
	requestArgument = request ListAt "Аргумент"

	jobToProcessThisEvent = entitiesFactory CreateEmptyJob
	self.machine DefineFieldHelper (request MessageSender) "Перед кем отчетность" (jobToProcessThisEvent JobFields)
	name = requestArgument TempClone
	name Concatenate "Запрос для /="
	messageSlot = entitiesFactory CreateReplyMessageSlot "Значение простым числом"
	jobToProcessThisEvent JobCreateStageWithNameMethodMessageSlotNameAndEntity name name name messageSlot
	object ObjectSetBasicMethod self &DivInPlaceSimple name
	
	request2 = entitiesFactory CreateEmptyMessage
	request2 MessageSetTypeRequest
	request2 MessageSetRequest "Значение простым числом"
	request2 MessageSetReceiver requestArgument
	processor SendMessage request2
	return self

ExternalNumberManipulator DivInPlaceSimple <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	job = (processor ContextJob)
	request = job JobMessageInMessageSlot "Значение простым числом"
	number /= (request NumberAt "Число")
	
	receiver = job JobFieldUIDWithName "Перед кем отчетность"
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetTypeReply
	reply MessageSetRequest "/="
	processor SendMessage reply
	return self

	
ExternalNumberManipulator Increment <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	number ++
	
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Инкремент"
	return self
	
	
ExternalNumberManipulator Decrement <Processor> processor
	object = processor ContextObject
	number = (object ObjectProperty "Число") AsNumber
	number --
	
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Декремент"
	return self
	

ExternalNumberManipulator Absolute <Processor> processor
	object = processor ContextObject
	number = ((object ObjectProperty "Число") AsNumber) Abs
	
	cloneUID = self.machine.machineManipulator.object CloneUIDObjectInternalRoutine processor.contextUID
	clone = self.machine UIDToObject cloneUID
	
	(clone ObjectProperties) AtPut "Число" number
	
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply AtPut "Значение" cloneUID
	processor SendReplyForMessage reply "Модуль"
	return self

