<MachineScheduler> <Queue> queue

MachineScheduler Init
	self.queue = <Queue>
	return self

MachineScheduler <List> GetNextUID
	if self.queue IsEmpty
		return nil
	else
		return self.queue Pop

MachineScheduler ScheduleUID <List> uid
	self.queue Push uid
	return self

MachineScheduler Destroy
	self.queue Release
	return self Destroy

MachineScheduler DeepClone
	return self

MachineScheduler Clone
	return self

MachineScheduler Compare <MachineScheduler> scheduler
	return equal
