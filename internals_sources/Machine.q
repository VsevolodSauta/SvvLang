<Machine> <ListMap> objectsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> processor <MachineScheduler> scheduler


Machine Init
	self.objectsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>
	self.processor = <Processor>
	self.processor SetMachine self
	self.scheduler = <MachineScheduler>
	return self


Machine LoadApplication <List> applicationName
	DEBUG_PUSH ("Machine: Loading application.")
	autoreleasePool ++
	console PrintLnString "Загружаем приложение."
	file = <File>
	file OpenForReading applicationName
	if file ErrorWhileOpenning
		console PrintLnString "Возникла ошибка при загрузке приложения. Невозможно прочитать приложение."
	contents = file ReadContentsOfFile
	file Close
	console PrintLnNumber (contents Size)
	console PrintLnString contents
	parsedObject = json ParseObject (contents First)
	if parsedObject == json.error
		console PrintLnString "Некорректный текст приложения. Невозможно провести грамматический разбор."
		autoreleasePool --
		return self
	self.globalContext AtPut ((parsedObject ListMapAt "Объект") ListAt "Имя") parsedObject
	uid = self.uidGenerator GetUID
	self.objectsByUIDs AtPut uid parsedObject
	uids = <List>
	parsedObject AtPut ("Идентификаторы") uids
	uids PushBack uid
	uids Release
	messageList = <List>
	parsedObject AtPut ("Сообщения") messageList
	messageList Release
	self.scheduler Schedule uid
	autoreleasePool --
	DEBUG_POP ("Machine: Application loaded.")
	return self


Machine <ListMap> ObjectByUID (ObjectFormUID UIDToObject) <List> uid
	return ((self.objectsByUIDs At uid) AsListMap)

Machine SetObjectByUID (SetObjectFromUID SetUIDToObject) <ListMap> object <List> uid
	self.objectsByUIDs AtPut uid object
	return self

Machine <List> GetUID
	return self.uidGenerator GetUID


Machine RestorePreviousState
	console PrintLnString ("Этот метод виртуальной машины не реализован. Не обращайте внимания. :)")
	return self


Machine Schedule <List> uid
	self.scheduler Schedule uid
	return self


Machine Run
	console PrintLnString ("Машина запущена.")
	if true
		self LoadApplication "Приложение"
	else
		self RestorePreviousState
	loop
		object = self.scheduler GetNextObject
		if object == nil
			console PrintLnString ("Планировщик времени не выдал объект. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.")
			break
		else
			self.processor ProcessObject object
	return self


Machine Destroy
	DEBUG_PUSH ("Machine: Destroying.")
	self.objectsByUIDs Release
	self.globalContext Release
	self.uidGenerator Release
	self.scheduler Release
	def self Destroy
	DEBUG_POP ("Machine: Destroyed.")

Machine Clone
	return self

Machine DeepClone
	return self

Machine <Comparation> Compare <Machine> machine
	return equal

