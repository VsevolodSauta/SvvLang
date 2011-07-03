<ExternalMachineManipulator> <Machine> machine <ExternalActorManipulator> actor <ExternalConsoleManipulator> console <ExternalFileManipulator> file <ExternalNumberManipulator> number <ExternalListManipulator> list <ExternalListMapManipulator> listMap <ExternalCharManipulator> char <ExternalJSONParserManipulator> jsonParser


ExternalMachineManipulator Init
	self.actor = <ExternalActorManipulator>
	self.console = <ExternalConsoleManipulator>
	self.file = <ExternalFileManipulator>
	self.number = <ExternalNumberManipulator>
	self.list = <ExternalListManipulator>
	self.listMap = <ExternalListMapManipulator>
	self.char = <ExternalCharManipulator>
	self.jsonParser = <ExternalJSONParserManipulator>
	return self


ExternalMachineManipulator Destroy
	self.actor Release
	self.console Release
	self.file Release
	self.number Release
	self.list Release
	self.listMap Release
	self.char Release
	self.jsonParser Release
	return self Destroy


ExternalMachineManipulator Clone
	return self Retain


ExternalMachineManipulator DeepClone
	return self Retain


ExternalMachineManipulator <Comparation> Compare <ExternalMachineManipulator> machineManipulator
	return equal


ExternalMachineManipulator SetMachine <Machine> machine
	self.machine = machine
	self.actor SetMachine machine
	self.console SetMachine machine
	self.file SetMachine machine
	self.number SetMachine machine
	self.list SetMachine machine
	self.listMap SetMachine machine
	self.char SetMachine machine
	self.jsonParser SetMachine machine
	return self


ExternalMachineManipulator CreateAll
	actorUID = self.actor CreateUIDActor

	consoleUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.console CreateUIDConsoleFromUIDActor consoleUID
	self.machine RegisterAtGlobalContext consoleUID "Консоль"

	fileUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.file CreateUIDFileFromUIDActor fileUID
	self.machine RegisterAtGlobalContext fileUID "Файл"

	numberUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.number CreateUIDNumberFromUIDActor numberUID
	self.machine RegisterAtGlobalContext numberUID "Число"

	listUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.list CreateUIDListFromUIDActor listUID
	self.machine RegisterAtGlobalContext listUID "Список"

	listMapUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.listMap CreateUIDListMapFromUIDActor listMapUID
	self.machine RegisterAtGlobalContext listMapUID "Отображение списков"

	charUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.char CreateUIDCharFromUIDActor charUID
	self.machine RegisterAtGlobalContext charUID "Символ"

	jsonParserUID = self.actor CloneUIDActorInternalRoutine actorUID
	self.jsonParser CreateUIDJSONParserFromUIDActor charUID
	self.machine RegisterAtGlobalContext jsonParserUID "Создатель объектов"

	console PrintLnString "==============="
	((self.machine UIDToActor actorUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor consoleUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor fileUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor numberUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor listUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor listMapUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor charUID) ActorJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToActor jsonParserUID) ActorJobs) DumpKeys
	console PrintLnString "==============="

	return self
