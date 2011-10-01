<MachineScheduler@Object> <Queue> queue

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
	return super Destroy
