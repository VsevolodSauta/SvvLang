<ExternalActorsFactory@Object> <Machine> machine

@actorsFactory

ExternalActorsFactory Destroy
	self.machine Release
	return super Destroy

ExternalActorsFactory SetMachine <Machine> machine
	self.machine = machine
	return self


ExternalActorsFactory <List> CreateActorFromObject <Object> value
	if value TypeIsNumber
		return self CreateNumber value
	elif value TypeIsList
		return self CreateList value
	elif value TypeIsListMap
		return self CreateListMap value
	elif value TypeIsChar
		return self CreateChar value
	console PrintLnString "Попытка создания объекта неивестного типа."
	return nil

ExternalActorsFactory <List> CreateNumber <Number> number
	uid = self.machine.fakeProcessor FieldNameToUID "Число"
	toReturn = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine uid
	(self.machine UIDToActor toReturn) ActorSetProperty number "Число"
	return toReturn


ExternalActorsFactory <List> CreateChar <Char> char
	uid = self.machine.fakeProcessor FieldNameToUID "Символ"
	toReturn = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine uid
	(self.machine UIDToActor toReturn) ActorSetProperty char "Символ"
	return toReturn


ExternalActorsFactory <List> CreateString <List> string
	uid = self.machine.fakeProcessor FieldNameToUID "Строка"
	toReturn = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine uid
	(self.machine UIDToActor toReturn) ActorSetProperty string "Строка"
	return toReturn


ExternalActorsFactory <List> CreateList <List> list
	uid = self.machine.fakeProcessor FieldNameToUID "Список"
	toReturn = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine uid
	(self.machine UIDToActor toReturn) ActorSetProperty list "Список"
	(self.machine UIDToActor toReturn) ActorSetProperty (entitiesFactory CreateEmptyList) "Список объектов"
	return toReturn


ExternalActorsFactory <List> CreateListMap <ListMap> listMap
	uid = self.machine.fakeProcessor FieldNameToUID "Отображение списков"
	toReturn = self.machine.machineManipulator.actor CloneUIDActorInternalRoutine uid
	(self.machine UIDToActor toReturn) ActorSetProperty listMap "Отображение списков"
	(self.machine UIDToActor toReturn) ActorSetProperty (entitiesFactory CreateEmptyList) "Список объектов"
	return toReturn
