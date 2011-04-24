<ExternalMachineManipulator> <Machine> machine <ExternalObjectManipulator> object <ExternalConsoleManipulator> console <ExternalFileManipulator> file <ExternalNumberManipulator> number <ExternalListManipulator> list

ExternalMachineManipulator Init
	self.object = <ExternalObjectManipulator>
	self.console = <ExternalConsoleManipulator>
	self.file = <ExternalFileManipulator>
	self.number = <ExternalNumberManipulator>
	self.list = <ExternalListManipulator>
	return self

ExternalMachineManipulator Destroy
	self.object Release
	self.console Release
	self.file Release
	self.number Release
	self.list Release
	return self Destroy

ExternalMachineManipulator Clone
	return self Retain

ExternalMachineManipulator DeepClone
	return self Retain

ExternalMachineManipulator <Comparation> Compare <ExternalMachineManipulator> machineManipulator
	return equal

ExternalMachineManipulator SetMachine <Machine> machine
	self.machine = machine
	self.object SetMachine machine
	self.console SetMachine machine
	self.file SetMachine machine
	self.number SetMachine machine
	self.list SetMachine machine
	return self

ExternalMachineManipulator CreateAll
	objectUID = self.object CreateUIDObject

	consoleUID = self.object CloneUIDObjectInternalRoutine objectUID
	self.console CreateUIDConsoleFromUIDObject consoleUID
	self.machine RegisterAtGlobalContext consoleUID "Консоль"

	fileUID = self.object CloneUIDObjectInternalRoutine objectUID
	self.file CreateUIDFileFromUIDObject fileUID
	self.machine RegisterAtGlobalContext fileUID "Файл"

	numberUID = self.object CloneUIDObjectInternalRoutine objectUID
	self.number CreateUIDNumberFromUIDObject numberUID
	self.machine RegisterAtGlobalContext numberUID "Число"

	listUID = self.object CloneUIDObjectInternalRoutine objectUID
	self.list CreateUIDListFromUIDObject listUID
	self.machine RegisterAtGlobalContext listUID "Список"

	console PrintLnString "==============="
	((self.machine UIDToObject objectUID) ObjectJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToObject consoleUID) ObjectJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToObject fileUID) ObjectJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToObject numberUID) ObjectJobs) DumpKeys
	console PrintLnString "==============="
	((self.machine UIDToObject listUID) ObjectJobs) DumpKeys
	console PrintLnString "==============="

	return self
