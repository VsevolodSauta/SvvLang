<Processor> <ListMap> [Retain] contextObject <ListMap> [Retain] contextJobStage <ListMap> [Retain] contextJob <Machine> machine <Stack> localNamespaces <Stack> helperStack <ListMap> processorCodes

Processor Init
	self.localNamespaces = <Stack>
	self.helperStack = <Stack>
	self.processorCodes = <ListMap>
	return self

Processor <Processor> Clone
	return <Processor>

Processor <Processor> DeepClone
	return <Processor>

Processor Destroy
	self.contextObject Release
	self.contextJobStage Release
	self.helperStack Release
	self.localNamespaces Release
	return self Destroy


Processor <Comparation> Compare <Processor> processor
	return equal


Processor SetMachine <Machine> machine
	self.machine = machine
	return self


Processor <List> LocationType <List> objectName
	candidate = ((self.localNamespaces Peek) AsListMap) ObjectAt objectName
	if candidate != nil
		return ("Локальное поле")
	candidate = (self.contextJob ListMapAt ("Поля"))  ObjectAt objectName
	if candidate != nil
		return ("Поле работы")
	candidate = (self.contextObject ListMapAt ("Поля")) ObjectAt objectName
	if candidate != nil
		return ("Поле объекта")
	candidate = (self.machine.globalContext) ObjectAt objectName
	if candidate != nil
		return ("Глобальное поле")
	else
		return ("Нет такого поля")


Processor <Synonim> ResolveName <List> objectName
	candidate = ((self.localNamespaces Peek) AsListMap) SynonimAt objectName
	if candidate != nil
		return candidate
	candidate = (self.contextJob ListMapAt ("Поля"))  SynonimAt objectName
	if candidate != nil
		return candidate
	candidate = (self.contextObject ListMapAt ("Поля")) SynonimAt objectName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt objectName
	return candidate


Processor SendMessage <ListMap> message
	uid = message ListAt ("Получатель")
	receiver = self.machine ObjectByUID uid
	messageList = (receiver ListAt ("Сообщения"))
	messageList PushBack message
	self.machine Schedule uid
	return self

Processor DoHelper <ListMap> toDo
	action = toDo ListAt ("Действие")
	if action == nil
		console PrintLnString ("Некорректное toDo: отсутствует действие.")
	elif action == ("Вызвать Do")
		value = (toDo At ("Аргумент"))
		if value == nil
			value = (self.helperStack Pop)
		self Do value
	elif action == ("Разрешить имя") // Пусть будет для "Создать поле *"
		name = (toDo At ("Имя"))
		if name == nil
			name = (self.helperStack Pop)
		self.helperStack Push (self ResolveName name)
	elif action == ("Взять объект из синонима")
		synonim = (toDo At ("Синоним"))
		if synonim == nil
			synonim = (self.helperStack Pop)
		self.helperStack Push ((synonim AsSynonim) Object)
	elif action == ("Добавить текущий объект в вершину")
		self.helperStack Push self.contextObject
	elif action == ("Добавить текущую работу в вершину")
		self.helperStack Push self.contextJob
	elif action == ("Добавить текущую стадию в вершину")
		self.helperStack Push self.contextJobStage
	elif action == ("Добавить список в вершину")
		list = (toDo At ("Список"))
		if list == nil
			list = <List>
			list Autorelease
		self.helperStack Push list
	elif action == ("Добавить отображение в вершину")
		listMap = (toDo At ("Отображение"))
		if listMap == nil
			listMap = <ListMap>
			listMap Autorelease
		self.helperStack Push listMap
	elif action == ("Удалить вершину")
		self.helperStack Pop
	elif action == ("Добавить элемент в отображение")
		key = (toDo At ("Ключ"))
		value = (toDo At ("Значение"))
		if value = nil
			value = (self.helperStack Pop)
		if key == nil
			key = (self.helperStack Pop)
		((self.helperStack Peek) AsListMap) AtPut key value
	elif action == ("Добавить элемент в список")
		value = (toDo At ("Значение"))
		if value = nil
			value = (self.helperStack Pop)
		((self.helperStack Peek) AsList) Append value
	elif action == ("Добавить в стек")
		self.helperStack Push (toDo ObjectAt ("Значение"))
	elif action == ("Дублировать вершину")
		self.helperStack Push (self.helperStack Peek)
	elif action == ("Поменять местами вершинные элементы")
		a = self.helperStack Pop
		b = self.helperStack Pop
		self.helperStack Push a
		self.helperStack Push b
	elif action == ("Вызвать DoHelper")
		value = (toDo At ("Аргумент"))
		if value = nil
			value = (self.helperStack Pop)
		self DoHelper value
	else
		console PrintLnString ("Некорректное toDo: неизвестное действие.")
	DEBUG_POP ("Processor: DONEHelper.")
	return self

Processor Do <ListMap> toDo
	DEBUG_PUSH ("Processor: DO.")
	action = toDo ListAt ("Действие")
	if action == nil
		console PrintLnString ("Некорректное toDo: отсутствует действие.")
	elif action == ("Послать сообщение")
		self SendMessage (toDo ListMapAt ("Сообщение"))
	elif action == ("Вызвать метод")
		self InvokeMethod (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Параметры"))
	elif action == ("Определить метод")
		(self.contextObject ListMapAt ("Методы")) AtPut (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Метод"))
	elif action == ("Удалить метод")
		(self.contextObject ListMapAt ("Методы")) RemoveAt (toDo ListAt ("Имя метода"))
	elif action == ("Создать ТВА")
		synonim = toDo SynonimAt ("Синоним")
		if synonim == nil
			name = toDo ListAt ("Существующее имя поля")
			if name == nil
				console PrintLnString ("Некорректные параметры для действия \"Создать ТВА\".")
				DEBUG_POP ("Processor: DONE.")
				return self
			synonim = self ResolveName name
		reference = <ListMap>
		reference AtPut ("Пространство имен") ((self.localNamespaces Peek) AsListMap)
		reference AtPut ("Имя поля") (toDo ListAt ("Имя поля"))
		synonim AddReference reference
		reference Release
	elif action == ("Создать поле работы")
		synonim = toDo SynonimAt ("Синоним")
		if synonim == nil
			name = toDo ListAt ("Существующее имя поля")
			if name == nil
				console PrintLnString ("Некорректные параметры для действия \"Создать поле работы\".")
				DEBUG_POP ("Processor: DONE.")
				return self
			synonim = self ResolveName name
		reference = <ListMap>
		reference AtPut ("Пространство имен") (self.contextJob  ListMapAt ("Поля"))
		reference AtPut ("Имя поля") (toDo ListAt ("Имя поля"))
		synonim AddReference reference
		reference Release
	elif action == ("Создать поле объекта")
		synonim = toDo SynonimAt ("Синоним")
		if synonim == nil
			name = toDo ListAt ("Существующее имя поля")
			if name == nil
				console PrintLnString ("Некорректные параметры для действия \"Создать поле объекта\".")
				DEBUG_POP ("Processor: DONE.")
				return self
			synonim = self ResolveName name
		reference = <ListMap>
		reference AtPut ("Пространство имен") (self.contextObject ListMapAt ("Поля"))
		reference AtPut ("Имя поля") (toDo ListAt ("Имя поля"))
		synonim AddReference reference
		reference Release
	elif action == ("Создать глобальное поле")
		synonim = toDo SynonimAt ("Синоним")
		if synonim == nil
			name = toDo ListAt ("Существующее имя поля")
			if name == nil
				console PrintLnString ("Некорректные параметры для действия \"Создать глобальное поле\".")
				DEBUG_POP ("Processor: DONE.")
				return self
			synonim = self ResolveName name
		reference = <ListMap>
		reference AtPut ("Пространство имен") self.machine.globalContext
		reference AtPut ("Имя поля") (toDo ListAt ("Имя поля"))
		synonim AddReference reference
		reference Release
	elif action == ("Присвоить")
		(self ResolveName (toDo ListAt ("Имя поля"))) SetObject (toDo ListAt ("Идентификатор"))
	elif action == ("Перемежить")
		(self ResolveName (toDo ListAt ("Имя поля"))) Unite (self ResolveName (toDo ListAt ("Имя прибытия")))
	elif action == ("Удалить поле")
		locationType = toDo At ("Пространство имен")
		if locationType == nil
			locationType = self LocationType (toDo ListAt ("Имя поля"))
		place = <ListMap>
		place AtPut ("Имя") (toDo ListAt ("Имя поля"))
		if locationType == ("Локальное поле")
			place AtPut ("Пространство имен") (self.localNamespaces Peek)
		elif locationType == ("Поле работы")
			place AtPut ("Пространство имен") ((self.contextJobStage ListMapAt ("Работа")) ListMapAt ("Поля"))
		elif locationType == ("Поле объекта")
			place AtPut ("Пространство имен") (self.contextObject ListMapAt ("Поля"))
		elif locationType == ("Глобальное поле")
			place AtPut ("Пространство имен") self.machine.globalContext
		else
			console PrintLnString ("Попытка удалить несуществующее поле.")
			place Release
			DEBUG_POP ("Processor: DONE.")
			return self
		synonim = self ResolveName (toDo ListAt ("Имя поля"))
		synonim RemoveReference place
		place Release
	elif action == ("Добавить работу")
		(self.contextObject ListAt ("Работы")) Append (toDo ListMapAt ("Работа"))
	elif action == ("Добавить следующую стадию")
		((toDo ListMapAt ("Работа")) ListAt ("Стадии")) Append (toDo ListMapAt ("Стадия"))
	elif action == ("Добавить условие входа на стадию")
		stage = toDo ListMapAt ("Стадия")
		(stage ListAt ("Ожидаемые сообщения")) Append (toDo ListMapAt ("Условие"))
		(stage NumberAt ("Необходимо сообщений")) ++
	elif action == ("Очистить стадии")
		((toDo ListMapAt ("Работа")) ListAt ("Стадии")) RemoveAll
	elif action == ("Завершить работу")
		console PrintLnString "Завершение работы"
		(self.contextObject ListAt ("Работы")) RemoveFirst (toDo ListMapAt ("Работа"))
	else
		console PrintLnString ("Некорректное toDo: неизвестное действие.")
	DEBUG_POP ("Processor: DONE.")
	return self


Processor InvokeMethod <List> methodName <ListMap> parameters
	DEBUG_PUSH ("Processor: Invoking method.")
	autoreleasePool ++
	method = (self.contextObject ListMapAt ("Методы")) ListMapAt methodName
	if method == nil
		console PrintLnString ("Ошибка! Вызов несуществующего метода.")
		autoreleasePool --
		DEBUG_POP ("Processor: Method processed.")
		return self
	if method LogicAt ("Базовый")
		adressConstant = ("Адрес")
		externalObjectEntity = self.contextObject At ("Сущность")
		object = self.contextObject
		C ((BasicMethod) ListMap_ObjectAt(_method, _adressConstant))(_externalObjectEntity, _object, _parameters);
	else
		namespace = <ListMap>
		self.localNamespaces Push namespace
		namespace AddListMap parameters
		namespace Release
		methodBody = (method At ("Тело")) AsList
		iterator = methodBody First
		while iterator NotThisEnd
			self DoHelper (iterator ListMapData)
			iterator ++
		self.localNamespaces Pop
	autoreleasePool --
	DEBUG_POP ("Processor: Method processed.")
	return self


Processor MessageConfirmsToParameter <ListMap> message <ListMap> parameter
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == ("Совпадение")
		if (message At (parameter At ("Ключ"))) == (parameter At ("Значение"))
			return true
	return false


Processor TryLinkMessageWithJobStage <ListMap> jobStage <ListMap> message
	DEBUG_PUSH ("Processor: Trying to link message with a job.")
	messagesIterator = (jobStage ListAt ("Ожидаемые сообщения")) First
	while messagesIterator NotThisEnd
		parametersIterator = (messagesIterator ListData) First
		confirms = true
		while parametersIterator NotThisEnd
			parameter = parametersIterator ListMapData
			if self NotMessageConfirmsToParameter message parameter
				confirms = false
				break
			parametersIterator ++
		if confirms
			(messagesIterator ListMapData) AtPut ("Сообщение") message
			msgNeeded = (jobStage NumberAt ("Необходимо сообщений"))
			msgNeeded --
			if msgNeeded == 0
				jobStage AtPut ("Состояние") ("Готовность")
		messagesIterator ++
	DEBUG_POP ("Processor: Message linking ended.")
	return self


Processor ProcessOneMessage
	DEBUG_PUSH ("Processor: Processing message.")
	messageList = (self.contextObject ListAt ("Сообщения"))
	if messageList NotIsEmpty
		message = messageList PopFront
		if message != nil
			jobsIterator = (self.contextObject ListAt ("Работы")) First
			while jobsIterator NotThisEnd
				job = jobsIterator ListMapData
				jobStagesIterator = (job ListAt ("Стадии")) First
				while jobStagesIterator NotThisEnd
					self TryLinkMessageWithJobStage message (jobStagesIterator ListMapData)
					jobStagesIterator ++
				jobsIterator ++
	DEBUG_POP ("Processor: Message processed.")
	return self


Processor ProcessOneJobIfAny
	DEBUG_PUSH ("Processor: Processing job.")
	jobsIterator = (self.contextObject ListAt ("Работы")) First
	while jobsIterator NotThisEnd
		job = (jobsIterator ListMapData)
		jobStagesIterator = (job ListAt ("Стадии")) First
		while jobStagesIterator NotThisEnd
			jobStage = jobStagesIterator ListMapData
			console PrintLnString (jobStage ListAt ("Состояние"))
			if (jobStage ListAt ("Состояние")) == ("Готовность")
				jobsIterator Hide
				jobStagesIterator Hide
				self.contextJobStage = jobStage
				self.contextJob = job
				emptyParameters = <ListMap>
				self InvokeMethod (jobStage ListAt ("Метод")) emptyParameters
				emptyParameters Release
				self.contextJobStage = nil
				self.contextJob = nil
				DEBUG_POP ("Processor: Job processed.")
				return self
			jobStagesIterator ++
		jobsIterator ++
	DEBUG_POP ("Processor: Job processed.")
	return self


Processor ProcessObject <List> uid
	DEBUG_PUSH ("Processor: Processing object.")
	autoreleasePool ++
	object = self.machine ObjectByUID uid
	self.contextObject = object
	self ProcessOneMessage
	self ProcessOneJobIfAny
	self.contextObject = nil
	autoreleasePool --
	DEBUG_POP ("Processor: Object processed.")
	return self

