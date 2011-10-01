<Machine@Object> <ListMap> actorsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> fakeProcessor <List> processors <MachineScheduler> scheduler <ExternalMachineManipulator> machineManipulator <Number> [Retain] totalProcessors <ExternalActorsFactory> actorsFactory


Machine Init
	// Это инициализация глобальной переменной.
	self.actorsFactory = <ExternalActorsFactory>
	self.actorsFactory SetMachine self

	self.totalProcessors = 1

	self.actorsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>

	self.fakeProcessor = <Processor>
	self.fakeProcessor SetMachine self

	self.processors = <List>
	i = 0
	while i < self.totalProcessors
		processor = <Processor>
		processor SetMachine self
		self.processors Add processor
		processor Release
		i ++

	self.scheduler = <MachineScheduler>
	self.machineManipulator = <ExternalMachineManipulator>
	self.machineManipulator SetMachine self
	self.machineManipulator CreateAll
	return self

Machine Destroy
	self.actorsByUIDs Release
	self.globalContext Release
	self.uidGenerator Release
	self.scheduler Release
	self.processors Release
	self.fakeProcessor Release
	return super Destroy


Machine <ExternalActorsFactory> ActorsFactory
	return self.actorsFactory

Machine <List> LoadActorWithNameToNamespace <List> actorName <ListMap> namespace
	(threadManager AutoreleasePool) ++
	console PrintString "Загружаем актор "
	console PrintLnString actorName
	file = <File>
	file OpenForReading actorName
	if file ErrorWhileOpenning
		console PrintLnString "Возникла ошибка при загрузке объекта. Невозможно прочитать контейнер объекта (как правило файл)."
	contents = file ReadContentsOfFile
	file Close
	parsedActor = jsonParser ParseObject (contents First)
	if parsedActor == jsonParser.error
		console PrintLnString "Некорректный текст объекта. Невозможно провести грамматический разбор."
		(threadManager AutoreleasePool) --
		return self
	uid = self.uidGenerator GenerateUID
	self SetUIDToActor uid parsedActor

	// SVV: Здесь необходимо проверить необходимость работы актора и его добавить в очередь необходимое число раз.
	self ScheduleUID uid

	self.fakeProcessor DefineFieldInNameSpaceWithUID ((parsedActor ActorProperties) ListAt "Имя") namespace uid
	(threadManager AutoreleasePool) --
	return uid

Machine <List> ImportActor (LoadActor) <List> actorName
	return self LoadActorWithNameToNamespace actorName self.globalContext

Machine RegisterAtGlobalContext <List> uid <List> name
	self.fakeProcessor DefineFieldInNameSpaceWithUID name self.globalContext uid
	return self


Machine <ListMap> UIDToActor (ActorByUID ActorFormUID) <List> uid
	return ((self.actorsByUIDs At uid) AsListMap)

Machine SetUIDToActor <List> uid <ListMap> actor
	self.actorsByUIDs AtPut uid actor
	((actor ActorProperties) ListAt ("Идентификаторы")) PushBack uid
	return self

Machine <List> GenerateUID (GetUID)
	return self.uidGenerator GenerateUID

Machine RestorePreviousState
	console PrintLnString ("Этот метод виртуальной машины не реализован. Не обращайте внимания. :)")
	return self


Machine ScheduleUID <List> uid
	self.scheduler ScheduleUID uid
	return self

Machine ProcessorFinishedWork <Processor> processor
	self.processors Add processor
	return self

Machine Run
	console PrintLnString ("Машина запущена.")
	loop
		// self CollectGarbage
		allProcessorsAreIdling = no
		if self.processors IsEmpty
			C OSwait4(-1, 0, 0, 0);
		if (self.processors Size) == self.totalProcessors
			allProcessorsAreIdling = yes
		processor = ((self.processors Pop) AsProcessor)

		uid = self.scheduler GetNextUID
		if (uid == nil) And (allProcessorsAreIdling)
			console PrintLnString ("Планировщик времени не выдал объект, все объекты ожидают. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.")
			break
		elif uid != nil
			processor ProcessUID uid
		else
			self.processors Add processor
			C OSwait4(-1, 0, 0, 0);
	return self


// Сборка мусора

Machine CollectGarbageProcessListMap <ListMap> listMap <List> notToDeleteList
	iterator = listMap First
	while iterator NotThisEnd
		if (iterator ThisData) TypeIsList
			self CollectGarbageProcessList (iterator ThisData) notToDeleteList
		elif (iterator ThisData) TypeIsListMap
			self CollectGarbageProcessListMap (iterator ThisData) notToDeleteList
		iterator ++
	return self

Machine CollectGarbageProcessList <List> list <List> notToDeleteList
	if list LooksLikeString
		notToDeleteList AppendIfAbsent list
	else
		iterator = list First
		while iterator NotThisEnd
			if (iterator ThisData) TypeIsList
				self CollectGarbageProcessList (iterator ThisData) notToDeleteList
			elif (iterator ThisData) TypeIsListMap
				self CollectGarbageProcessListMap (iterator ThisData) notToDeleteList
			iterator ++
	return self


Machine CollectGarbage
	(threadManager AutoreleasePool) ++
	notToDeleteList = <List>
	iterator1 = self.globalContext First
	while iterator1 NotThisEnd
		notToDeleteList Add (((iterator1 ThisData) AsSynonim) UID)
		iterator1 ++

	iterator1 = self.actorsByUIDs First
	while iterator1 NotThisEnd
		iterator2 = (iterator1 ListMapData) ActorJobsIterator
		while iterator2 NotThisEnd
			iterator3 = (iterator2 ListMapData) JobMessageSlotsIterator
			while iterator3 NotThisEnd
				iterator4 = ((iterator3 ListMapData) MessageSlotMessages) First
				while iterator4 NotThisEnd
					message = iterator4 ListMapData
					self CollectGarbageProcessListMap message notToDeleteList
					iterator4 ++
				iterator3 ++
			iterator2 ++
		iterator1 ++

	iterator1 = notToDeleteList First
	while iterator1 NotThisEnd
		actor = (self UIDToActor (iterator1 ThisData))
		if actor != nil
			iterator2 = (actor ActorFields) First
			while iterator2 NotThisEnd
				notToDeleteList AppendIfAbsent (((iterator2 ThisData) AsSynonim) UID)
				iterator2 ++

			iterator2 = (actor ActorJobs) First
			while iterator2 NotThisEnd
				iterator3 = ((iterator2 ListMapData) JobFields) First
				while iterator3 NotThisEnd
					notToDeleteList AppendIfAbsent (((iterator3 ThisData) AsSynonim) UID)
					iterator3 ++
				iterator2 ++
		iterator1 ++

	toDeleteList = <List>
	iterator1 = self.actorsByUIDs First
	while iterator1 NotThisEnd
		if notToDeleteList NotContains (iterator1 Key)
			toDeleteList Add (iterator1 Key)
		iterator1 ++

	iterator1 = toDeleteList First

	while iterator1 NotThisEnd
		(iterator1 ListData) PrintLn
		self.actorsByUIDs RemoveKey (iterator1 ListData)
		iterator1 ++

	notToDeleteList Release
	toDeleteList Release

	(threadManager AutoreleasePool) --
	return self
