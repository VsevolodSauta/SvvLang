<ExternalObjectManipulator> <Machine> machine

ExternalObjectManipulator Init
	return self

ExternalObjectManipulator Clone
	return self

ExternalObjectManipulator Destroy
	return self Destroy

ExternalObjectManipulator Compare
	return equal

ExternalObjectManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalObjectManipulator <List> ObjectCreate
	autoreleasePool ++
	console PrintLnString ("Создаем объект.")
	object = <ListMap>
	messageList = <List>				// Список сообщений. Фактически очередь в данной реализации.
	methods = <ListMap>				// Отображение имен методов в список действий.
	fields = <ListMap>				// Отображение имен полей в их uidы.
	jobs = <List>					// Список работ.
	properties = <ListMap>				// Для внутреннего использования. Пока не часть публичного API.
	uids = <List>					// Для последующей оптимизации. Использование для быстрого клонирования.
	uid = self.machine GetUID
	uids PushBack uid
	object AtPut ("Методы") methods
	object AtPut ("Поля") fields
	object AtPut ("Свойства") properties
	object AtPut ("Работы") jobs
	object AtPut ("Сообщения") messageList
	object AtPut ("Идентификаторы") uids
	self.machine SetUIDToObject uid object
	object Release
	jobs Release
	fields Release
	properties Release
	methods Release
	messageList Release
	uids Release
	autoreleasePool --
	return uid

ExternalObjectManipulator <List> ObjectClone <List> uid
	object = self.machine ObjectByUID uid
	uidToReturn = self.machine GetUID
	objectToReturn = object DeepClone
	self.machine SetUIDToObject uidToReturn objectToReturn
	objectToReturn Release
	return uidToReturn

ExternalObjectManipulator <List> SetBasicMethodForObjectWithName methodAdress <List> uid <List> name
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Адрес") methodAdress
	method AtPut ("Базовый") true
	methods AtPut name method
	method Release
	return self

ExternalObjectManipulator <List> SetMethodForObjectWithName methodBody <List> uid <List> name
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Тело") methodBody
	method AtPut ("Базовый") false
	methods AtPut name method
	method Release
	return self
