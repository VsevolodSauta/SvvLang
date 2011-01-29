<ExternalObjectManipulator> <Machine> machine

ExternalObjectManipulator Init
	return self

ExternalObjectManipulator Clone
	return self

ExternalObjectManipulator Destroy
	return self Destroy

ExternalObjectManipulator Compare <ExternalObjectManipulator> manipulator
	return equal

ExternalObjectManipulator SetMachine <Machine> machine
	self.machine = machine
	return self

ExternalObjectManipulator <List> CreateUID
	autoreleasePool ++
	self.machine LoadUIDWithNameToNamespace "Объект" self.machine.globalContext
	autoreleasePool --
	return uid

ExternalObjectManipulator <List> CloneUID <List> uid
	object = self.machine ObjectByUID uid
	uidToReturn = self.machine GenerateUID
	objectToReturn = object DeepClone
	self.machine SetUIDToObject uidToReturn objectToReturn
	objectToReturn Release
	return uidToReturn

ExternalObjectManipulator <List> SetBasicMethodWithNameForUID <Method> method <List> name <List> uid
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Базовый метод") method
	method AtPut ("Базовый") true
	methods AtPut name method
	method Release
	return self

ExternalObjectManipulator <List> SetMethodWithNameForUID <List> methodBody <List> name <List> uid
	object = self.machine ObjectByUID uid
	methods = object ListMapAt ("Методы")
	method = <ListMap>
	method AtPut ("Тело") methodBody
	method AtPut ("Базовый") false
	methods AtPut name method
	method Release
	return self
