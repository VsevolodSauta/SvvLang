<Processor> <ListMap> [Retain] contextObject <ListMap> [Retain] contextJobStage <Machine> machine <Stack> localNamespaces <Stack> helperStack


Processor Init
	self.localNamespaces = <Stack>
	self.helperStack = <Stack>
	return self


Processor <Processor> Clone
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
	candidate = ((self.contextJobStage ListMapAt ("Работа")) ListMapAt ("Поля"))  ObjectAt objectName
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
	candidate = ((self.contextJobStage ListMapAt ("Работа")) ListMapAt ("Поля"))  SynonimAt objectName
	if candidate != nil
		return candidate
	candidate = (self.contextObject ListMapAt ("Поля")) SynonimAt objectName
	if candidate != nil
		return candidate
	candidate = (self.machine.globalContext) SynonimAt objectName
	return candidate


Processor SendMessage <ListMap> message
	receiver = self.machine ObjectByUID (message ListAt ("Получатель"))
	messageQueue = (receiver QueueAt ("Сообщения"))
	messageQueue Push message
	self.machine Schedule receiver
	return self

Processor DoHelper <ListMap> toDo
	action = toDo ListAt ("Действие")
	if action == nil
		console PrintLnString ("Некорректное toDo: отсутствует действие.")
	elif action == ("Вызвать Do")
		value = (toDo At ("Аргумент"))
		if value = nil
			value = (self.helperStack Pop)
		self Do value
	elif action == ("Создать список")
		list = <List>
		self.helperStack Push list
		list Release
	elif action == ("Создать отображение")
		listMap = <ListMap>
		self.helperStack Push listMap
		listMap Release
	elif action == ("Удалить вершину")
		self.helperStack Pop
	elif action == ("Добавить в отображение элемент")
		key = (toDo At ("Ключ"))
		value = (toDo At ("Значение"))
		if value = nil
			value = (self.helperStack Pop)
		if key == nil
			key = (self.helperStack Pop)
		((self.helperStack Peek) AsListMap) AtPut key value
	elif action == ("Добавить в список элемент")
		value = (toDo At ("Значение"))
		if value = nil
			value = (self.helperStack Pop)
		((self.helperStack Peek) AsList) Append value
	elif action == ("Добавить в стек")
		self.helperStack Push (toDo ObjectAt ("Значение"))
	elif action == ("Дублировать")
		self.helperStack Push (self.helperStack Peek)
	elif action == ("Вызвать DoHelper")
		value = (toDo At ("Аргумент"))
		if value = nil
			value = (self.helperStack Pop)
		self DoHelper value
	else
		console PrintLnString ("Некорректное toDo: неизвестное действие.")
	return self
	

Processor Do <ListMap> toDo
	action = toDo ListAt ("Действие")
	if action == nil
		console PrintLnString ("Некорректное toDo: отсутствует действие.")
	elif action == ("Послать сообщение")
		self SendMessage (toDo ListMapAt ("Сообщение"))
	elif action == ("Определить метод")
		methodEntity = <ListMap>
		methodEntity AtPut ("Базовый") (toDo LogicAt ("Базовый"))
		methodEntity AtPut ("Тело") (toDo ListAt ("Тело метода"))
		methodEntity AtPut ("Адрес") (toDo ListAt ("Адрес"))
		methodEntity Release
		(self.contextObject ListMapAt ("Методы")) AtPut (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Метод"))
	elif action == ("Вызвать метод")
		self InvokeMethod (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Параметры"))
	elif action == ("Удалить метод")
		(self.contextObject ListMapAt ("Методы")) RemoveAt (toDo ListAt ("Имя метода"))
	elif action == ("Создать ТВА")
		((self.localNamespaces Peek) AsListMap) Add (toDo ListAt ("Имя поля")) (toDo SynonimAt ("Синоним"))
	elif action == ("Создать поле работы")
		((self.contextJobStage ListMapAt ("Работа"))  ListMapAt ("Поля")) Add (toDo ListAt ("Имя поля")) (toDo SynonimAt ("Синоним"))
	elif action == ("Создать поле объекта")
		(self.contextObject ListMapAt ("Поля")) Add (toDo ListAt ("Имя поля")) (toDo SynonimAt ("Синоним"))
	elif action == ("Создать глобальное поле")
		(self.machine.globalContext AtPut (toDo ListAt ("Имя поля")) (toDo SynonimAt ("Синоним")))
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
		(self.contextObject ListAt ("Работы")) RemoveFirst (toDo ListMapAt ("Работа"))
	else
		console PrintLnString ("Некорректное toDo: неизвестное действие.")
	return self


Processor InvokeMethod <List> methodName <ListMap> parameters
	autoreleasePool ++
	method = (self.contextObject ListMapAt ("Методы")) ListMapAt methodName
	if method == nil
		console PrintLnString ("Ошибка! Вызов несуществующего метода.")
		autoreleasePool --
		return self
	if method LogicAt ("Базовый")
		adressConstant = ("Адрес")
		object = self.contextObject
		C ((BasicMethod) ListMap_ObjectAt(_method, _adressConstant))(_object, _parameters);
	else
		namespace = <ListMap>
		self.localNamespaces Push namespace
		namespace Release
		methodBody = (method At ("Тело")) AsList
		iterator = methodBody First
		while iterator NotThisEnd
			self DoHelper (iterator ListMapData)
			iterator ++
		self.localNamespaces Pop
	autoreleasePool --
	return self


Processor MessageConfirmsToParameter <ListMap> message <ListMap> parameter
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == ("Совпадение")
		if (message At (parameter At ("Тип"))) == (parameter At ("Значение"))
			return true
	return false


Processor TryLinkMessageWithJobStage <ListMap> jobStage <ListMap> message
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
	return self


Processor ProcessOneMessage
	message = (self.contextObject QueueAt ("Сообщения")) Pop
	jobsIterator = (self.contextObject ListAt ("Работы")) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		jobStagesIterator = (job ListAt ("Стадии")) First
		while jobStagesIterator NotThisEnd
			self TryLinkMessageWithJobStage message (jobStagesIterator ListMapData)
			jobStagesIterator ++
		jobsIterator ++
	return self


Processor ProcessOneJobIfAny
	jobsIterator = (self.contextObject ListAt ("Работы")) First
	while jobsIterator NotThisEnd
		job = (jobsIterator ListMapData)
		jobStagesIterator = (job ListAt ("Стадии")) First
		while jobStagesIterator NotThisEnd
			jobStage = jobStagesIterator ListMapData
			if (jobStage ListAt ("Cостояние")) == ("Готовность")
				jobsIterator Hide
				jobStagesIterator Hide
				self.contextJobStage = jobStage
				emptyParameters = <ListMap>
				self InvokeMethod (jobStage ListAt ("Метод")) emptyParameters
				emptyParameters Release
				self.contextJobStage = nil
				return self
			jobStagesIterator ++
		jobsIterator ++
	return self


Processor ProcessObject <ListMap> object
	autoreleasePool ++
	self.contextObject = object
	self ProcessOneMessage
	self ProcessOneJobIfAny
	self.contextObject = nil
	autoreleasePool --
	return self

