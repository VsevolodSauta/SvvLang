<ExternalEntitiesFactory> placeHolder

ExternalEntitiesFactory Clone
	return self Retain

ExternalEntitiesFactory DeepClone
	return self Retain

ExternalEntitiesFactory Destroy
	return self Destroy

ExternalEntitiesFactory Compare <ExternalEntitiesFactory> entitiesFactory
	return equal

ExternalEntitiesFactory <ListMap> CreateEmptyListMap
	toReturn = <ListMap>
	return toReturn Autorelease
	
ExternalEntitiesFactory <List> CreateEmptyList
	toReturn = <List>
	return toReturn Autorelease

ExternalEntitiesFactory <ListMap> CreateEmptyJob
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Поля" (self CreateEmptyListMap)
	toReturn AtPut "Сообщения" (self CreateEmptyListMap)
	toReturn AtPut "Стадии" (self CreateEmptyListMap)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyMethod
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Базовый" false
	toReturn AtPut "Тело" (self CreateEmptyList)
	return toReturn	

ExternalEntitiesFactory <ListMap> CreateEmptyJobStage
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Сообщения" (self CreateEmptyList)
	toReturn AtPut "Метод" (self CreateEmptyList)
	toReturn AtPut "Необходимо сообщений" 0
	return toReturn

ExternalEntitiesFactory <ListMap> CreateConditionPresence <List> key
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод проверки" "Совпадение"
	toReturn AtPut "Ключ" ""
	toReturn AtPut "Значение" ""
	return toReturn
	
ExternalEntitiesFactory <ListMap> CreateConditionEquality (CreateConditionWithKeyValue) <List> key value
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод проверки" "Совпадение"
	toReturn AtPut "Ключ" (key TempClone)
	toReturn AtPut "Значение" (value TempClone)
	return toReturn
	
ExternalEntitiesFactory <ListMap> CreateEmptyMessageSlot
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод идентификации" (self CreateEmptyList)
	toReturn AtPut "Стадии" (self CreateEmptyList)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateRequestMessageSlot <List> request
	toReturn = self CreateEmptyMessageSlot
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Тип" "Запрос")
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Запрос" request)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateObject
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Методы" (self CreateEmptyMethods)
	toReturn AtPut "Поля" (self CreateEmptyFields)
	toReturn AtPut "Свойства" (self CreateEmptyProperties)
	toReturn AtPut "Работы" (self CreateEmptyJobs)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyFields
	return self CreateEmptyListMap

ExternalEntitiesFactory <ListMap> CreateEmptyMethods
	return self CreateEmptyListMap

ExternalEntitiesFactory <ListMap> CreateEmptyJobs
	return self CreateEmptyListMap

ExternalEntitiesFactory <ListMap> CreateEmptyProperties
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Идентификаторы" (self CreateEmptyList)
	toReturn AtPut "Имя" (self CreateEmptyList)
	return toReturn

