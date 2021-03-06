<ExternalFileManipulator@Object> <Machine> machine

ExternalFileManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalFileManipulator <List> CreateUIDFileFromUIDActor <List> uid
	actor = self.machine ActorByUID uid

	actor ActorSetBasicMethod self &ExternalFileManipulator_AssociateUIDFileBasicMethod "Ассоциировать имя фала"
	actor ActorSetBasicMethod self &ExternalFileManipulator_OpenForReadingUIDFileBasicMethod "Открыть файл для чтения"
	actor ActorSetBasicMethod self &ExternalFileManipulator_OpenForWritingUIDFileBasicMethod "Открыть файл для записи"
	actor ActorSetBasicMethod self &ExternalFileManipulator_CloseUIDFileBasicMethod "Закрыть файл"
	actor ActorSetBasicMethod self &ExternalFileManipulator_ReadStringUIDFileBasicMethod "Прочитать строку"
	actor ActorSetBasicMethod self &ExternalFileManipulator_WriteStringUIDFileBasicMethod "Записать строку"
	actor ActorSetBasicMethod self &ExternalFileManipulator_WriteActorUIDFileBasicMethod "Записать объект"

	job = entitiesFactory CreateEmptyJob
	actor ActorSetJob job "Основная работа файла"
	messageSlot = entitiesFactory CreateRequestMessageSlot "Ассоциировать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Имя файла")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Ассоциирование файла" "Ассоциировать имя фала" "Запрос на ассоциирование" messageSlot
	return uid


ExternalFileManipulator AssociateUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = (processor ContextJob)
	(fileActor ActorProperties) AtPut "Имя файла" (processor EntityFromNamedMessageField "Запрос на ассоциирование" "Имя файла")
	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Чтение")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для чтения" "Открыть файл для чтения" "Запрос на открытие файла для чтения"  messageSlot
	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Запись")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для записи" "Открыть файл для записи" "Запрос на открытие файла для записи"  messageSlot

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на ассоциирование"

	return self



ExternalFileManipulator OpenForReadingUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = (processor ContextJob)
	file = <File>
	file OpenForReading (fileActor ActorProperty "Имя файла")
	(fileActor ActorSetProperty file "Файл"
	file Release

	messageSlot = entitiesFactory CreateRequestMessageSlot "Прочитать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект чтения" "Строка")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Чтение строки" "Прочитать строку" "Запрос для чтения строки" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Закрыть"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Закрытие файла" "Закрыть файл" "Запрос на закрытие файла" messageSlot

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на открытие файла для чтения"

	job JobRemoveStageAndMessageSlots "Ассоциирование файла"
	job JobRemoveStageAndMessageSlots "Открытие файла для чтения"
	job JobRemoveStageAndMessageSlots "Открытие файла для записи"
	return self


ExternalFileManipulator OpenForWritingUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = (processor ContextJob)
	file = <File>
	file OpenForAppending (fileActor ActorProperty "Имя файла")
	fileActor ActorSetProperty file "Файл"
	file Release

	messageSlot = entitiesFactory CreateRequestMessageSlot "Записать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект записи" "Простая строка")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Простая строка")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Запись простой строки" "Записать простую строку" "Запрос для записи простой строки" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Записать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект записи" "Объект")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Объект")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Запись объекта" "Записать объект" "Запрос для записи объекта" messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Закрыть"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Закрытие файла" "Закрыть файл" "Запрос на закрытие файла" messageSlot

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на открытие файла для записи"

	job JobRemoveStageAndMessageSlots "Ассоциирование файла"
	job JobRemoveStageAndMessageSlots "Открытие файла для чтения"
	job JobRemoveStageAndMessageSlots "Открытие файла для записи"
	return self

ExternalFileManipulator CloseUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = (processor ContextJob)
	file = (fileActor ActorProperty "Файл") AsFile
	file Close
	fileActor ActorSetProperty nil "Файл"

	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Чтение")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для чтения" "Открыть файл" "Запрос на открытие файла для чтения"  messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Запись")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для записи" "Открыть файл" "Запрос на открытие файла для записи"  messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Ассоциировать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Имя файла")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Ассоциирование файла" "Ассоциировать имя фала" "Запрос на ассоциирование" messageSlot

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на закрытие файла"

	job JobRemoveStageAndMessageSlots "Записать строку"
	job JobRemoveStageAndMessageSlots "Прочитать строку"
	job JobRemoveStageAndMessageSlots "Закрытие файла"
	return self


ExternalFileManipulator WriteStringUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = (processor ContextJob)
	file = (fileActor ActorProperty "Файл") AsFile
	file WriteNakedString (processor EntityFromNamedMessageField "Запрос для записи строки" "Строка")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос для записи строки"
	return self


ExternalFileManipulator WriteActorUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	job = entitiesFactory CreateEmptyJob
	uidToWrite = (processor EntityFromNamedMessageField "Запрос для записи объекта" "Объект")
	fileActor ActorSetJob job ("Вывод " Concatenate uidToWrite)

	messageSlot = processor CreateStageReplyEntityBasicMethodInJob "Значение простой строкой" self &ExternalFileManipulator_WriteSecondStageUIDFileBasicMethod job
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Ответ" "Успех")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Строка")

	processor DefineFieldInNameSpaceWithUID "Заказчик" (job JobFields) (processor EntityFromNamedMessageField "Запрос для записи объекта" "Отправитель")

	request = entitiesFactory CreateEmptyMessage
	request MessageSetTypeRequest
	request MessageSetRequest "Значение простой строкой"
	request MessageSetReceiver uidToWrite
	processor SendMessage request
	return self


ExternalFileManipulator WriteSecondStageUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	file = (fileActor ActorProperty "Файл") AsFile
	file WriteNakedString (processor EntityFromNamedMessageField "Значение простой строкой" "Строка")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetRequest "Запрос для записи объекта"
	reply MessageSetReceiver (processor FieldNameToUID "Заказчик")
	processor SendMessage reply
	return self


ExternalFileManipulator ReadStringUIDFileBasicMethod <Processor> processor
	fileActor = (processor ContextActor)
	file = (fileActor ActorProperty "Файл") AsFile
	string = file ReadString
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply AtPut "Строка" string
	processor SendReplyForMessage reply "Запрос для чтения строки"
	return self
