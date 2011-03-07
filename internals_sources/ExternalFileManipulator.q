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
	
ExternalFileManipulator CreateUIDFileFromUIDObject <List> uid
	object = self.machine ObjectByUID uid
	
	object ObjectSetBasicMethod self &ExternalFileManipulator_AssociateUIDFileBasicMethod "Ассоциировать имя фала"
	object ObjectSetBasicMethod self &ExternalFileManipulator_OpenForReadingUIDFileBasicMethod "Открыть файл для чтения"
	object ObjectSetBasicMethod self &ExternalFileManipulator_OpenForWritingUIDFileBasicMethod "Открыть файл для записи"
	object ObjectSetBasicMethod self &ExternalFileManipulator_CloseUIDFileBasicMethod "Закрыть файл"
	object ObjectSetBasicMethod self &ExternalFileManipulator_ReadStringUIDFileBasicMethod "Прочитать строку"
	object ObjectSetBasicMethod self &ExternalFileManipulator_WriteStringUIDFileBasicMethod "Записать строку"
	
	job = entitiesFactory CreateEmptyJob
	object ObjectSetJob job "Основная работа файла"
	messageSlot = entitiesFactory CreateRequestMessageSlot "Ассоциировать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Имя файла")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Ассоциирование файла" "Ассоциировать имя фала" "Запрос на ассоциирование" messageSlot
	return uid


ExternalFileManipulator AssociateUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	(fileObject ObjectProperties) AtPut "Имя файла" (job JobFieldInMessageSlot "Имя файла" "Запрос на ассоциирование")
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
	(fileObject ObjectSetProperty "Файл" file
	file Release

	messageSlot = entitiesFactory CreateRequestMessageSlot "Прочитать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект чтения" "Строка")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Чтение строки" "Прочитать строку" "Запрос для чтения строки" messageSlot
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "Закрыть"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Закрытие" "Закрыть файл" "Запрос на закрытие" messageSlot
	
	job JobRemoveStageAndMessageSlots "Ассоциировать"
	job JobRemoveStageAndMessageSlots "Открыть для чтения"
	job JobRemoveStageAndMessageSlots "Открыть для записи"

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на открытие файла"
	return self


ExternalFileManipulator OpenForWritingUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = <File>
	file OpenForAppending (fileObject ObjectProperty "Имя файла")
	fileObject ObjectSetProperty "Файл" file
	file Release

	messageSlot = entitiesFactory CreateRequestMessageSlot "Записать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Объект записи" "Строка")
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Строка")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Запись строки" "Записать строку" "Запрос для записи строки" messageSlot
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "Закрыть"
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Закрытие файла" "Закрыть файл" "Запрос на закрытие" messageSlot

	job JobRemoveStageAndMessageSlots "Ассоциировать"
	job JobRemoveStageAndMessageSlots "Открыть для чтения"
	job JobRemoveStageAndMessageSlots "Открыть для записи"

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на открытие файла"
	return self

ExternalFileManipulator CloseUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = (fileObject ObjectProperty "Файл") AsFile
	file Close
	fileObject ObjectSetProperty "Файл" nil
	
	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Чтение")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для чтения" "Открыть файл" "Запрос на открытие файла для чтения"  messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Открыть"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionWithKeyValue "Доступ" "Запись")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Открытие файла для записи" "Открыть файл" "Запрос на открытие файла для записи"  messageSlot

	messageSlot = entitiesFactory CreateRequestMessageSlot "Ассоциировать"
	messageSlot MessageSlotSetCondition (entitiesFactory CreateConditionPresence "Имя файла")
	job JobCreateStageWithNameMethodMessageSlotNameAndEntity "Ассоциирование файла" "Ассоциировать имя фала" "Запрос на ассоциирование" messageSlot

	job JobRemoveStageAndMessageSlots "Записать строку"
	job JobRemoveStageAndMessageSlots "Прочитать строку"
	job JobRemoveStageAndMessageSlots "Закрытие файла"

	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос на закрытие файла"
	return self


ExternalFileManipulator WriteStringUIDFileBasicMethod <Processor> processor
	fileObject = (processor ContextObject)
	job = (processor ContextJob)
	file = (fileObject ObjectProperty "Файл") AsFile
	file WriteNakedString (job JobFieldInMessageSlot "Строка" "Запрос для записи строки")
	reply = entitiesFactory CreateEmptyMessage
	reply MessageSetAnswerSuccess
	processor SendReplyForMessage reply "Запрос для записи строки"
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


