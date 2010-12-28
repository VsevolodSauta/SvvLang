<MachineScheduler> placeholder

MachineScheduler <ListMap> GetNextObject
	console PrintLnString ("Этот метод планировщика виртуального процессора виртуальной машины не реализован.")
	return nil

MachineScheduler Destroy
	return self Destroy

MachineScheduler Clone
	return self

MachineScheduler Compare <MachineScheduler> scheduler
	return equal

