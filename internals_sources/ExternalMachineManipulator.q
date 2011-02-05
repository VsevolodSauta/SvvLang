<ExternalMachineManipulator> <Machine> machine <ExternalObjectManipulator> object <ExternalConsoleManipulator> console

ExternalMachineManipulator Init
	self.object = <ExternalObjectManipulator>
	self.console = <ExternalConsoleManipulator>
	return self

ExternalMachineManipulator Destroy
	self.object Release
	self.console Release
	return self Destroy

ExternalMachineManipulator Clone
	return self Retain

ExternalMachineManipulator DeepClone
	return self Retain

ExternalMachineManipulator Compare <ExternalMachineManipulator> machineManipulator
	return self

ExternalMachineManipulator SetMachine <Machine> machine
	self.machine = machine
	self.object SetMachine machine
	self.console SetMachine machine
	return self

ExternalMachineManipulator CreateAll
	objectUID = self.object CreateUIDObject
	"Object created." PrintLn
	consoleUID = self.object CloneUIDObjectInternalRoutine objectUID
	"Console created." PrintLn
	self.console CreateUIDConsoleFromUIDObject consoleUID
	return self
