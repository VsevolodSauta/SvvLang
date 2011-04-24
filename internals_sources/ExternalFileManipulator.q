<ExternalFileManipulator> <Machine> machine

ExternalFileManipulator Init
	return self

ExternalFileManipulator Clone
	return self

ExternalFileManipulator DeepClone
	return self

ExternalFileManipulator Destroy
	return self Destroy

ExternalFileManipulator <Comparation> Compare <ExternalFileManipulator> consoleManipulator
	return equal

ExternalFileManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalFileManipulator <List> CreateUIDFileFromUIDObject <List> uid
	object = self.machine ObjectByUID uid

	object ObjectSetBasicMethod self &ExternalFileManipulator_AssociateUIDFileBasicMethod "Ассоциировать имя фала"
	object ObjectSetBasicMethod self &ExternalFileManipulator_OpenForReadingUIDFileBasicMethod "Открыть файл для чтения"
	object ObjectSetBasicMethod self &ExternalFileManipulator_OpenForWritingUIDFileBasicMethod "Открыть файл для записи"
	object ObjectSetBasicMethod self &ExternalFileManipulator_CloseUIDFileBasicMethod "Закрыть файл"
	object ObjectSetBasicMethod self &ExternalFileManipulator_ReadStringUIDFileBasicMethod "Прочитать строку"
	object ObjectSetBasicMethod self &ExternalFileManipulator_WriteStringUIDFileBasicMethod "Записать строку"
	object ObjectSetBasicMethod self &ExternalFileManipulator_WriteObjectUIDFileBasicMethod "Записать объект"

	job = entitiesFactory CreateEmptyJob
	object ObjectSetJob job "Основная работа файла"
	messageSlot = entitiesFactory CreateRequestMessageSlot "Ассоциировать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Имя файла")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Ассоциирование файла" "Ассоциировать имя фала" "Запрос на ассоциирование" messageSlot
	return uid


ExternalFileManipulator AssociateUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	(fileObject ObjectProperties) AtPut "Имя файла" (processor EntityFromNamedMessageField "Запрос на ассоциирование" "Имя файла")
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
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = <File>
	file OpenForReading (fileObject ObjectProperty "Имя файла")
	(fileObject ObjectSetProperty file "Файл"
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
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = <File>
	file OpenForAppending (fileObject ObjectProperty "Имя файла")
	fileObject ObjectSetProperty file "Файл"
	file Release

	messageSlot = entitiesFactory CreateRequestMessageSlot "Записать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект записи" "Строка")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Строка")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Запись строки" "Записать строку" "Запрос для записи строки" messageSlot

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
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = (fileObject ObjectProperty "Файл") AsFile
	file Close
	fileObject ObjectSetProperty nil "Файл"

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
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = (fileObject ObjectProperty "Файл") AsFile
	file WriteNakedString (processor EntityFromNamedMessageField "Запрос для записи строки" "Строка")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос для записи строки"
	return self


ExternalFileManipulator WriteObjectUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = entitiesFactory CreateEmptyJob
	uidToWrite = (processor EntityFromNamedMessageField "Запрос для записи объекта" "Объект")
	fileObject ObjectSetJob job ("Вывод " Concatenate uidToWrite)

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
	fileObject = (processor ContextObject)
	file = (fileObject ObjectProperty "Файл") AsFile
	file WriteNakedString (processor EntityFromNamedMessageField "Значение простой строкой" "Строка")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply MessageSetRequest "Запрос для записи объекта"
	reply MessageSetReceiver (processor FieldNameToUID "Заказчик")
	processor SendMessage reply
	return self


ExternalFileManipulator ReadStringUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	file = (fileObject ObjectProperty "Файл") AsFile
	string = file ReadString
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	reply AtPut "Строка" string
	processor SendReplyForMessage reply "Запрос для чтения строки"
	return self
