<ExternalObjectsFactory> <Machine> machine

ExternalObjectsFactory Init
	return self

ExternalObjectsFactory Destroy
	self.machine Release
	return self Destroy

ExternalObjectsFactory <Comparation> Compare eof
	return equal

ExternalObjectsFactory Clone
	return self Retain

ExternalObjectsFactory DeepClone
	return self Retain

ExternalObjectsFactory SetMachine <Machine> machine
	self.machine = machine
	return self


ExternalObjectsFactory <List> CreateValue <Object> value
	if value TypeIsNumber
		return self CreateNumber value
	elif value TypeIsList
		return self CreateList value
	elif value TypeIsListMap
		return self CreateListMap value
	console PrintLnString "Попытка создания объекта неивестного типа."
	return nil

ExternalObjectsFactory <List> CreateNumber <Number> number
	uid = self.machine.fakeProcessor FieldNameToUID "Число"
	toReturn = self.machine.machineManipulator.object CloneUIDObjectInternalRoutine uid
	(self.machine UIDToObject toReturn) ObjectSetProperty number "Число"
	return toReturn


ExternalObjectsFactory <List> CreateString <List> string
	uid = self.machine.fakeProcessor FieldNameToUID "Строка"
	toReturn = self.machine.machineManipulator.object CloneUIDObjectInternalRoutine uid
	(self.machine UIDToObject toReturn) ObjectSetProperty string "Строка"
	return toReturn


ExternalObjectsFactory <List> CreateList <List> list
	uid = self.machine.fakeProcessor FieldNameToUID "Список"
	toReturn = self.machine.machineManipulator.object CloneUIDObjectInternalRoutine uid
	(self.machine UIDToObject toReturn) ObjectSetProperty list "Список"
	(self.machine UIDToObject toReturn) ObjectSetProperty (entitiesFactory CreateEmptyList) "Список объектов"
	return toReturn


ExternalObjectsFactory <List> CreateListMap <ListMap> listMap
	uid = self.machine.fakeProcessor FieldNameToUID "Строковое отображение"
	toReturn = self.machine.machineManipulator.object CloneUIDObjectInternalRoutine uid
	(self.machine UIDToObject toReturn) ObjectSetProperty listMap "Строковое отображение"
	return toReturn
