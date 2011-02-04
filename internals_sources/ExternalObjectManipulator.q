<ExternalObjectManipulator> <Machine> machine <ListMap> objectMasterCopy

ExternalObjectManipulator Init
	return self

ExternalObjectManipulator Clone
	return self

ExternalObjectManipulator DeepClone
	return self

ExternalObjectManipulator Destroy
	self.objectMasterCopy Release
	return self Destroy

ExternalObjectManipulator Compare <ExternalObjectManipulator> manipulator
	return equal

ExternalObjectManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalObjectManipulator <List> CreateUIDObject
	autoreleasePool ++
	uid = self.machine ImportUID "Объект"
	self SetBasicMethodWithNameForUID &ExternalObjectManipulator_CloneUIDObjectBasicMethod "Клонировать" uid
	self.objectMasterCopy = (self.machine UIDToObject uid) DeepClone
	autoreleasePool --
	return uid

ExternalObjectManipulator <List> SetBasicMethodWithNameForUID <Method> method <List> name <List> uid
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Базовый метод") method
	method AtPut ("Базовый") true
	methods AtPut name method
	method Release
	return self

ExternalObjectManipulator <List> SetMethodWithNameForUID <List> methodBody <List> name <List> uid
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Тело") methodBody
	method AtPut ("Базовый") false
	methods AtPut name method
	method Release
	return self

ExternalObjectManipulator CloneUIDObjectBasicMethod <List> uid <ListMap> parameters <Processor> processor
	object = self.machine UIDToObject uid
	uidToReturn = self.machine GenerateUID
	objectToReturn = self.objectMasterCopy DeepClone
	objectToReturn AtPut "Методы" ((object At "Методы") TempDeepClone)
	objectToReturn AtPut "Поля" ((object At "Поля") TempDeepClone)
	list = <List>
	(objectToReturn ListMapAt "Свойства") AtPut "Идентификаторы" list
	list Release
	self.machine SetUIDToObject uidToReturn objectToReturn
	objectToReturn Release
	receiver = processor EntityFromNamedMessageField "Сообщение на клонирование" "Получатель"
	sender = processor EntityFromNamedMessageField "Сообщение на клонирование" "Отправитель"
	message = <ListMap>
	message AtPut "Отправитель" receiver
	message AtPut "Получатель" sender
	message AtPut "Тип" "Ответ"
	message AtPut "Ответ" "Успех"
	message AtPut "Запрос" "Клонировать"
	message AtPut "Клон" uidToReturn
	processor SendMessage message
	message Release
	console PrintLnString "Сообщение послано. Ура!"
	return self
