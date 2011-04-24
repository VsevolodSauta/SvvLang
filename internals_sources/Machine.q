<Machine> <ListMap> objectsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> fakeProcessor <Processor> processor <MachineScheduler> scheduler <ExternalMachineManipulator> machineManipulator


Machine Init
	objectsFactory = <ExternalObjectsFactory>
	objectsFactory SetMachine self

	self.objectsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>

	self.fakeProcessor = <Processor>
	self.fakeProcessor SetMachine self

	self.processor = <Processor>
	self.processor SetMachine self

	self.scheduler = <MachineScheduler>
	self.machineManipulator = <ExternalMachineManipulator>
	self.machineManipulator SetMachine self
	self.machineManipulator CreateAll
	return self


Machine <List> LoadUIDWithNameToNamespace <List> objectName <ListMap> namespace
	autoreleasePool ++
	console PrintString "Загружаем объект "
	console PrintLnString objectName
	file = <File>
	file OpenForReading objectName
	if file ErrorWhileOpenning
		console PrintLnString "Возникла ошибка при загрузке объекта. Невозможно прочитать контейнер объекта (как правило файл)."
	contents = file ReadContentsOfFile
	file Close
	parsedObject = jsonParser ParseObject (contents First)
	if parsedObject == jsonParser.error
		console PrintLnString "Некорректный текст объекта. Невозможно провести грамматический разбор."
		autoreleasePool --
		return self
	uid = self.uidGenerator GenerateUID
	self SetUIDToObject uid parsedObject
	self ScheduleUID uid
	self.fakeProcessor DefineFieldInNameSpaceWithUID ((parsedObject ObjectProperties) ListAt "Имя") namespace uid
	autoreleasePool --
	return uid

Machine <List> ImportUID (LoadUID) <List> objectName
	return self LoadUIDWithNameToNamespace objectName self.globalContext

Machine RegisterAtGlobalContext <List> uid <List> name
	self.fakeProcessor DefineFieldInNameSpaceWithUID name self.globalContext uid
	return self


Machine <ListMap> UIDToObject (ObjectByUID ObjectFormUID) <List> uid
	return ((self.objectsByUIDs At uid) AsListMap)

Machine SetUIDToObject <List> uid <ListMap> object
	self.objectsByUIDs AtPut uid object
	((object ObjectProperties) ListAt ("Идентификаторы")) PushBack uid
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
	self.processor Release
	self.fakeProcessor Release
	return self Destroy

Machine Clone
	return self Retain

Machine DeepClone
	return self Retain

Machine <Comparation> Compare <Machine> machine
	return equal
