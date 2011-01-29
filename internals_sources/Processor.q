<Processor> <ListMap> [Retain] contextObject <ListMap> [Retain] contextJobStage <ListMap> [Retain] contextJob <Machine> machine <Stack> localNamespaces <Stack> helperStack <ListMap> processorCodes

Processor <Processor> Clone
	return <Processor>

Processor <Processor> DeepClone
	return <Processor>

Processor Destroy
	self.contextObject Release
	self.contextJobStage Release
	self.helperStack Release
	self.localNamespaces Release
	self.processorCodes Release
	return self Destroy

Processor <Comparation> Compare <Processor> processor
	return equal


Processor SetMachine <Machine> machine
	self.machine = machine
	return self

Processor Init
	self.localNamespaces = <Stack>
	self.helperStack = <Stack>
	self.processorCodes = <ListMap>
	self.processorCodes AtPut ("Выполнить") &Processor_DoCode
	self.processorCodes AtPut ("Взять сообщение из имени") &Processor_MessageFromMessageNameCode
	self.processorCodes AtPut ("Взять сущность из поля сообщения") &Processor_ObjectFromMessagesFieldCode
	self.processorCodes AtPut ("Взять синоним из поля") &Processor_FieldNameToSynonimCode
	self.processorCodes AtPut ("Взять объект из синонима") &Processor_SynonimToUIDCode
	self.processorCodes AtPut ("Добавить текущий объект в вершину") &Processor_AddCurrentObjectToStackCode
	self.processorCodes AtPut ("Добавить текущую работу в вершину") &Processor_AddCurrentJobToStackCode
	self.processorCodes AtPut ("Добавить текущую стадию в вершину") &Processor_AddCurrentJobStageToStackCode
	self.processorCodes AtPut ("Добавить список в вершину") &Processor_AddListToStackCode
	self.processorCodes AtPut ("Добавить отображение в вершину") &Processor_AddListMapToStackCode
	self.processorCodes AtPut ("Удалить вершину") &Processor_PopFromStackCode
	self.processorCodes AtPut ("Добавить элемент в отображение") &Processor_AddObjectToListMapCode
	self.processorCodes AtPut ("Добавить элемент в список") &Processor_AddObjectToListCode
	self.processorCodes AtPut ("Добавить в стек") &Processor_AddObjectToStackCode
	self.processorCodes AtPut ("Дублировать вершину") &Processor_DuplicateTopInStackCode
	self.processorCodes AtPut ("Поменять местами вершинные элементы") &Processor_SwapTopInStackCode
	self.processorCodes AtPut ("Послать сообщение") &Processor_SendMessageCode
	self.processorCodes AtPut ("Вызвать метод") &Processor_InvokeMethodCode
	self.processorCodes AtPut ("Определить метод") &Processor_DefineMethodCode
	self.processorCodes AtPut ("Удалить метод") &Processor_UnDefineMethodCode
	self.processorCodes AtPut ("Создать ТВА") &Processor_DefineLocalFieldCode
	self.processorCodes AtPut ("Создать поле работы") &Processor_DefineJobFieldCode
	self.processorCodes AtPut ("Создать поле объекта") &Processor_DefineObjectFieldCode
	self.processorCodes AtPut ("Создать глобальное поле") &Processor_DefineGlobalFieldCode
	self.processorCodes AtPut ("Присвоить") &Processor_SetFieldCode
	self.processorCodes AtPut ("Перемежить") &Processor_UniteFieldCode
	self.processorCodes AtPut ("Удалить поле") &Processor_UnDefineFieldCode
	self.processorCodes AtPut ("Добавить работу") &Processor_AddJobToObjectCode
	self.processorCodes AtPut ("Добавить следующую стадию") &Processor_AddStageToJobCode
	self.processorCodes AtPut ("Добавить условие входа на стадию") &Processor_AddConditionToStageCode
	self.processorCodes AtPut ("Очистить стадии") &Processor_RemoveAllStagesCode
	self.processorCodes AtPut ("Завершить работу") &Processor_FinishJobCode
	return self

Processor Do <ListMap> toDo
	console PrintLnString (toDo ListAt ("Действие"))
	method = self.processorCodes MethodAt (toDo ListAt ("Действие"))
	if method == nil
		console PrintLnString ("Некорректное toDo: Действие не существует либо отсутствует в системе комманд.")
	method Invoke self toDo
	return self

Processor DoCode <ListMap> toDo
	value = (toDo At ("Аргумент"))
	if value == nil
		value = (self.helperStack Pop)
	self Do value
	return self

Processor MessageFromMessageNameCode <ListMap> toDo
	name = (toDo At ("Имя сообщения"))
	if name == nil
		name = (self.helperStack Pop)
	message = (self.contextJob ListMapAt "Ожидаемые сообщения") ListMapAt name
	self.helperStack Push message
	return self


Processor ObjectFromMessagesFieldCode <ListMap> toDo
	name = (toDo At ("Имя поля"))
	if name == nil
		name = (self.helperStack Pop)
	message = (toDo At ("Сообщение"))
	if message == nil
		message = (self.helperStack Pop)
	self.helperStack Push ((message AsListMap) ObjectAt (name AsList))
	return self

Processor FieldNameToSynonimCode <ListMap> toDo
	name = (toDo At ("Имя"))
	if name == nil
		name = (self.helperStack Pop)
	self.helperStack Push (self FieldNameToSynonim name)
	return self

Processor SynonimToUIDCode <ListMap> toDo
	synonim = (toDo At ("Синоним"))
	if synonim == nil
		synonim = (self.helperStack Pop)
	self.helperStack Push ((synonim AsSynonim) UID)
	return self

Processor AddCurrentObjectToStackCode <ListMap> toDo
	self.helperStack Push self.contextObject
	return self

Processor AddCurrentJobToStackCode <ListMap> toDo
	self.helperStack Push self.contextJob
	return self

Processor AddCurrentJobStageToStackCode <ListMap> toDo
	self.helperStack Push self.contextJobStage
	return self

Processor AddListToStackCode <ListMap> toDo
	list = (toDo At ("Список"))
	if list == nil
		list = <List>
		list Autorelease
	self.helperStack Push list
	return self

Processor AddListMapToStackCode <ListMap> toDo
	listMap = (toDo At ("Отображение"))
	if listMap == nil
		listMap = <ListMap>
		listMap Autorelease
	self.helperStack Push listMap
	return self

Processor PopFromStackCode <ListMap> toDo
	self.helperStack Pop
	return self

Processor AddObjectToListMapCode <ListMap> toDo
	key = (toDo At ("Ключ"))
	value = (toDo At ("Значение"))
	if value == nil
		value = (self.helperStack Pop)
	if key == nil
		key = (self.helperStack Pop)
	((self.helperStack Peek) AsListMap) AtPut key value
	return self

Processor AddObjectToListCode <ListMap> toDo
	value = (toDo At ("Значение"))
	if value == nil
		value = (self.helperStack Pop)
	((self.helperStack Peek) AsList) Append value
	return self

Processor AddObjectToStackCode <ListMap> toDo
	self.helperStack Push (toDo ObjectAt ("Значение"))
	return self

Processor DuplicateTopInStackCode <ListMap> toDo
	self.helperStack Push ((self.helperStack Peek) TempClone)
	return self

Processor SwapTopInStackCode <ListMap> toDo
	a = self.helperStack Pop
	b = self.helperStack Pop
	self.helperStack Push a
	self.helperStack Push b
	return self

Processor SendMessageCode <ListMap> toDo
	self SendMessage (toDo ListMapAt ("Сообщение"))
	return self

Processor InvokeMethodCode <ListMap> toDo
	self InvokeMethodWithParameters (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Параметры"))
	return self

Processor DefineMethodCode <ListMap> toDo
	(self.contextObject ListMapAt ("Методы")) AtPut (toDo ListAt ("Имя метода")) (toDo ListMapAt ("Метод"))
	return self

Processor UnDefineMethodCode <ListMap> toDo
	(self.contextObject ListMapAt ("Методы")) RemoveAt (toDo ListAt ("Имя метода"))
	return self

Processor DefineLocalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo ((self.localNamespaces Peek) AsListMap)

Processor DefineJobFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo (self.contextJob  ListMapAt ("Поля"))

Processor DefineObjectFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo (self.contextObject ListMapAt ("Поля"))

Processor DefineGlobalFieldCode <ListMap> toDo
	return self DefineFieldHelper toDo self.machine.globalContext

Processor DefineFieldHelper <ListMap> toDo <ListMap> nameSpace
	synonim = toDo SynonimAt ("Синоним")
	if synonim == nil
		name = toDo ListAt ("Существующее имя поля")
		if name == nil
			console PrintLnString ("Некорректные параметры для \"Создать поле\".")
			return self
		synonim = self FieldNameToSynonim name
	reference = <ListMap>
	reference AtPut ("Пространство имен") nameSpace
	reference AtPut ("Имя поля") (toDo ListAt ("Имя поля"))
	synonim AddReference reference
	reference Release
	return self


Processor SetFieldCode <ListMap> toDo
	(self FieldNameToSynonim (toDo ListAt ("Имя поля"))) SetUID (toDo ListAt ("Идентификатор"))
	return self

Processor UniteFieldCode <ListMap> toDo
	(self FieldNameToSynonim (toDo ListAt ("Имя прибытия"))) Unite (self FieldNameToSynonim (toDo ListAt ("Имя поля")))
	return self

Processor UnDefineFieldCode <ListMap> toDo
	locationType = toDo ListAt ("Пространство имен")
	if locationType == nil
		locationType = self FieldNameToNamespaceName (toDo ListAt ("Имя поля"))
	place = <ListMap>
	place AtPut ("Имя") (toDo ListAt ("Имя поля"))
	place AtPut ("Пространство имен") (self NamespaceNameToNamespace locationType)
	synonim = self FieldNameToSynonim (toDo ListAt ("Имя поля"))
	synonim RemoveReference place
	place Release
	return self

Processor AddJobToObjectCode <ListMap> toDo
	(self.contextObject ListAt ("Работы")) Append (toDo ListMapAt ("Работа"))
	return self

Processor AddStageToJobCode <ListMap> toDo
	((toDo ListMapAt ("Работа")) ListAt ("Стадии")) Append (toDo ListMapAt ("Стадия"))
	return self

Processor AddConditionToStageCode <ListMap> toDo
	stage = toDo ListMapAt ("Стадия")
	(stage ListAt ("Ожидаемые сообщения")) Append (toDo ListMapAt ("Условие"))
	(stage NumberAt ("Необходимо сообщений")) ++
	return self

Processor RemoveAllStagesCode <ListMap> toDo
	((toDo ListMapAt ("Работа")) ListAt ("Стадии")) RemoveAll
	return self

Processor FinishJobCode <ListMap> toDo
	console PrintLnString "Завершение работы"
	(self.contextObject ListAt ("Работы")) RemoveFirst (toDo ListMapAt ("Работа"))
	return self

Processor <ListMap> NamespaceNameToNamespace <List> locationType
	if locationType == "Глобальное поле"
		return self.machine.globalContext
	elif locationType == "Поле объекта"
		return self.contextObject ListMapAt ("Поля")
	elif locationType == "Поле работы"
		return self.contextJob ListMapAt ("Поля")
	elif locationType == "Локальное поле"
		return self.localNamespaces Peek
	return nil

Processor <List> FieldNameToNamespaceName <List> objectName
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

Processor <Synonim> FieldNameToSynonim <List> objectName
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
	self ProcessMessageForObject message receiver
	self.machine ScheduleUID uid
	return self

Processor InvokeMethodWithParameters <List> methodName <ListMap> parameters
	autoreleasePool ++
	method = (self.contextObject ListMapAt ("Методы")) ListMapAt methodName
	if method == nil
		console PrintLnString ("Ошибка! Вызов несуществующего метода.")
	else
		if method LogicAt ("Базовый")
			basicMethod = method MethodAt ("Базовый метод")
			objectEntity = (self.contextObject ListMapAt ("Свойства")) ObjectAt ("Сущность")
			basicMethod Invoke objectEntity self.contextObject parameters
		else
			namespace = <ListMap>
			self.localNamespaces Push namespace
			namespace AddListMap parameters
			namespace Release
			methodBody = method ListAt ("Тело")
			iterator = methodBody First
			while iterator NotThisEnd
				self Do (iterator ListMapData)
				iterator ++
			self.localNamespaces Pop
	autoreleasePool --
	return self


Processor MessageConfirmsToParameter <ListMap> message <ListMap> parameter
	checkingMethod = parameter At ("Метод проверки")
	if checkingMethod == ("Совпадение")
		if (message At (parameter At ("Ключ"))) == (parameter At ("Значение"))
			return true
	return false


Processor TryLinkMessageWithMessageSlotAndJob <ListMap> message <ListMap> messageSlot <ListMap> job
	confirms = true
	parametersIterator = (messageSlot ListAt ("Метод идентификации")) First
	while parametersIterator NotThisEnd
		parameter = parametersIterator ListMapData
		if self NotMessageConfirmsToParameter message parameter
			confirms = false
			break
		parametersIterator ++
	if confirms
		messageSlot AtPut ("Сообщение") message
		waitingStageNamesIterator = (messageSlot ListAt ("Ожидающие стадии")) First
		while waitingStageNamesIterator NotThisEnd
			jobStage = (job ListMapAt ("Стадии")) ListMapAt (waitingStageNamesIterator ListData)
			msgNeeded = (jobStage NumberAt ("Необходимо сообщений"))
			msgNeeded --
			if msgNeeded == 0
				jobStage AtPut ("Состояние") ("Готовность")
	return self


Processor ProcessMessageForObject <ListMap> message <ListMap> object
	jobsIterator = (object ListMapAt ("Работы")) First
	while jobsIterator NotThisEnd
		job = jobsIterator ListMapData
		messageSlotsIterator = (job ListMapAt ("Ожидаемые сообщения")) First
		while messageSlotsIterator NotThisEnd
			self TryLinkMessageWithMessageSlotAndJob message (messageSlotsIterator ListMapData) job
			messageSlotsIterator ++
		jobsIterator ++
	return self


Processor ProcessOneJobIfAny
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
				self InvokeMethodWithParameters (jobStage ListAt ("Метод")) emptyParameters
				emptyParameters Release
				self.contextJobStage = nil
				self.contextJob = nil
				return self
			jobStagesIterator ++
		jobsIterator ++
	return self


Processor ProcessUID <List> uid
	autoreleasePool ++
	object = self.machine ObjectByUID uid
	self.helperStack Clean
	self.contextObject = object
	self ProcessOneJobIfAny
	self.contextObject = nil
	autoreleasePool --
	return self
