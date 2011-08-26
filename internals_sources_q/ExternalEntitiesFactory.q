<ExternalEntitiesFactory> placeHolder

@entitiesFactory

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
	toReturn AtPut "Ожидаемые сообщения" (self CreateEmptyListMap)
	toReturn AtPut "Стадии" (self CreateEmptyListMap)
	toReturn AtPut "Методы" (self CreateEmptyListMap)
	toReturn AtPut "Свойства" (self CreateEmptyListMap)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyMethod
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Базовый" false
	toReturn AtPut "Тело" (self CreateEmptyList)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateMethodWithBody <List> methodBody
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Базовый" false
	toReturn AtPut "Тело" methodBody
	return toReturn

ExternalEntitiesFactory <ListMap> CreateMethodWithEntityBasicMethod entity method
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Базовый" true
	toReturn AtPut "Базовый метод" method
	toReturn AtPut "Сущность" entity
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyJobStage
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Ожидаемые сообщения" (self CreateEmptyList)
	toReturn AtPut "Метод" (self CreateEmptyList)
	toReturn AtPut "Необходимо сообщений" 0
	toReturn AtPut "Состояние" "Готово"
	return toReturn

ExternalEntitiesFactory <ListMap> CreateConditionPresence <List> key
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод проверки" "Наличие"
	toReturn AtPut "Ключ" key
	return toReturn

ExternalEntitiesFactory <ListMap> CreateConditionEquality (CreateConditionWithKeyValue) <List> key value
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод проверки" "Совпадение"
	toReturn AtPut "Ключ" ((key Clone) Autorelease)
	toReturn AtPut "Значение" ((value DynamicallyClone) Autorelease)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateConditionEqualityWithField <List> key value
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод проверки" "Совпадение с полем"
	toReturn AtPut "Ключ" ((key Clone) Autorelease)
	toReturn AtPut "Значение" ((value DynamicallyClone) Autorelease)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyMessageSlot
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Метод идентификации" (self CreateEmptyList)
	toReturn AtPut "Стадии" (self CreateEmptyList)
	toReturn AtPut "Состояние" "Открыто"
	toReturn AtPut "Сообщения" (self CreateEmptyList)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateRequestMessageSlot <List> request
	toReturn = self CreateEmptyMessageSlot
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Тип" "Запрос")
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Запрос" request)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateReplyMessageSlot <List> request
	toReturn = self CreateEmptyMessageSlot
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Тип" "Ответ")
	toReturn MessageSlotSetCondition (self CreateConditionWithKeyValue "Запрос" request)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateActorProperties
	toReturn = (self CreateEmptyProperties)
	toReturn AtPut "Запросы на оповещение" (self CreateEmptyList)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyActor
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Методы" (self CreateEmptyMethods)
	toReturn AtPut "Поля" (self CreateEmptyFields)
	toReturn AtPut "Работы" (self CreateEmptyJobs)
	toReturn AtPut "Свойства" (self CreateActorProperties)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateMessageProperties
	toReturn = self CreateEmptyListMap
	toReturn AtPut "Ожидаемые сообщения" (self CreateEmptyList)
	return toReturn

ExternalEntitiesFactory <ListMap> CreateEmptyMessage
	toReturn = self CreateEmptyListMap
	attribs = self CreateEmptyListMap
	toReturn AtPut "Свойства" (self CreateMessageProperties)
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
	toReturn AtPut "Запросы на оповещение" (self CreateEmptyList)
	return toReturn
