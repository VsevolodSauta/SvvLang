<Machine> <ListMap> objectsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> processor <MachineScheduler> scheduler <ExternalMachineManipulator> machineManipulator


Machine Init
	self.objectsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>
	self.processor = <Processor>
	self.processor SetMachine self
	self.scheduler = <MachineScheduler>
	self.machineManipulator = <ExternalMachineManipulator>
	self.machineManipulator SetMachine self
	self.machineManipulator CreateAll
	file = <File>
	file OpenForAppending "Vasia"
	file WriteNakedString "Vasia porosya"
	file Close
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
	self DefineFieldHelper uid ((parsedObject ObjectProperties) ListAt "Имя") namespace
	autoreleasePool --
	return uid

Machine <List> ImportUID (LoadUID) <List> objectName
	return self LoadUIDWithNameToNamespace objectName self.globalContext

Machine RegisterAtGlobalContext <List> uid <List> name
	return self DefineFieldHelper uid name self.globalContext
	

Machine DefineFieldHelper <List> uid <List> fieldName <ListMap> nameSpace
	synonim = <Synonim>
	synonim SetUID uid
	reference = <ListMap>
	reference AtPut ("Пространство имен") nameSpace
	reference AtPut ("Имя поля") fieldName
	synonim AddReference reference
	reference Release
	synonim Release
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
	return self Destroy

Machine Clone
	return self

Machine DeepClone
	return self

Machine <Comparation> Compare <Machine> machine
	return equal

