<Machine> <ListMap> objectsByUIDs <UIDGenerator> uidGenerator <ListMap> globalContext <Processor> processor <MachineScheduler> scheduler


Machine Init
	self.objectsByUIDs = <ListMap>
	self.uidGenerator = <UIDGenerator>
	self.globalContext = <ListMap>
	self.processor = <Processor>
	self.processor SetMachine self
	self.scheduler = <MachineScheduler>
	return self


Machine CreateObject
	autoreleasePool ++
	console PrintLnString ("Создаем объект.")
	object = <ListMap>
	messageQueue = <Queue>				// Отображение uidа отправителя в список строк сообщений.
	methods = <ListMap>				// Отображение имен методов в список строк действий.
	fields = <ListMap>				// Отображение имен полей в их uidы.
	jobs = <List>					// Отображение имен работ в их состояния (стадии).
	properties = <ListMap>				// Список текущих свойств объекта --- его состояние.
	object AtPut ("Методы") methods
	object AtPut ("Поля") fields
	object AtPut ("Свойства") properties
	object AtPut ("Работы") jobs
	object AtPut ("Сообщения") messageQueue
	self.objectsByUIDs AtPut (self.uidGenerator getUID) object
	object Release
	jobs Release
	fields Release
	properties Release
	methods Release
	messageQueue Release
	def self
	autoreleasePool --


Machine <ListMap> ObjectByUID <List> uid
	return ((self.objectsByUIDs At uid) AsListMap)


Machine RestorePreviousState
	console PrintLnString ("Этот метод виртуальной машины не реализован. Не обращайте внимания. :)")
	return self


Machine Schedule <ListMap> object
	console PrintLnString ("Этот метод виртуальной машины не реализован. Не обращайте внимания. :)")
	return self


Machine Run
	console PrintLnString ("Машина запущена.")
	if true
		self CreateObject
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


Machine <Comparation> Compare <Machine> machine
	return equal

