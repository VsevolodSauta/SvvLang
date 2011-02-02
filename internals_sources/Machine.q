<Machine> <ListMap> objectsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> processor <MachineScheduler> scheduler


Machine Init
	self.objectsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>
	self.processor = <Processor>
	self.processor SetMachine self
	self.scheduler = <MachineScheduler>
	return self


Machine <List> LoadUIDWithNameToNamespace <List> objectName <ListMap> namespace
	autoreleasePool ++
	console PrintLnString "Загружаем объект."
	file = <File>
	file OpenForReading objectName
	if file ErrorWhileOpenning
		console PrintLnString "Возникла ошибка при загрузке объекта. Невозможно прочитать контейнер объекта (файл)."
	contents = file ReadContentsOfFile
	file Close
	console PrintLnNumber (contents Size)
	console PrintLnString contents
	parsedObject = json ParseObject (contents First)
	if parsedObject == json.error
		console PrintLnString "Некорректный текст приложения. Невозможно провести грамматический разбор."
		autoreleasePool --
		return self
	uid = self.uidGenerator GenerateUID
	self.objectsByUIDs AtPut uid parsedObject
	((parsedObject ListMapAt ("Свойства")) ListAt ("Идентификаторы")) PushBack uid
	self.scheduler ScheduleUID uid
	synonim = <Synonim>
	synonim SetUID uid
	synonim AddToNamespaceWithName namespace ((parsedObject ListMapAt "Свойства") ListAt "Имя")
	synonim Release
	autoreleasePool --
	return uid


Machine <ListMap> UIDToObject (ObjectByUID ObjectFormUID) <List> uid
	return ((self.objectsByUIDs At uid) AsListMap)

Machine SetUIDToObject <List> uid <ListMap> object
	self.objectsByUIDs AtPut uid object
	return self

Machine <List> GenerateUID (GetUID)
	return self.uidGenerator GenerateUID

Machine RestorePreviousState
	console PrintLnString ("Этот метод виртуальной машины не реализован. Не обращайте внимания. :)")
	return self


Machine ScheduleUID <List> uid
	self.scheduler ScheduleUID uid
	return self


Machine Run
	console PrintLnString ("Машина запущена.")
	if true
		self LoadUIDWithNameToNamespace ("Приложение") self.globalContext
	else
		self RestorePreviousState
	loop
		uid = self.scheduler GetNextUID
		if uid == nil
			console PrintLnString ("Планировщик времени не выдал объект. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.")
			break
		else
			self.processor ProcessUID uid
	return self


Machine Destroy
	self.objectsByUIDs Release
	self.globalContext Release
	self.uidGenerator Release
	self.scheduler Release
	return self Destroy

Machine Clone
	return self

Machine DeepClone
	return self

Machine <Comparation> Compare <Machine> machine
	return equal
