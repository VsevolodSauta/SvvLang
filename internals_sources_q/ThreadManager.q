<ThreadManager@Object> <Map> threadsByPidMap

@threadManager

ThreadManager Init
	self.threadsByPidMap = <Map>
	return self

ThreadManager Clone
	return self Retain

ThreadManager DeepClone
	return self Retain

ThreadManager <Comparison> CompareSameGID <ThreadManager> tm
	return (self Hash) ? (tm Hash)

ThreadManager Destroy
	self.threadsByPidMap Release
	return super Destroy

ThreadManager RegisterCurrentThread
	pid = self Pid
	if self.threadsByPidMap NotContainsKey pid
		thread = <Thread>
		thread SetPid pid
		self.threadsByPidMap AtPut pid thread
	pid Release
	return self

ThreadManager RegisterThread <Thread> thread
	pid = thread.pid
	if self.threadsByPidMap NotContainsKey pid
		self.threadsByPidMap AtPut pid thread
	return self

ThreadManager <AutoreleasePool> AutoreleasePool
	pid = self Pid
	autoreleasePool = ((self.threadsByPidMap At pid) AsThread) AutoreleasePool
	pid Release
	return autoreleasePool

ThreadManager SpawnThreadWithMethodAndEntity <Method> method entity
	C OSclone(0xf11, _method->entity, _entity);
	return self

// Непубличные методы.

ThreadManager <Number> Pid
	pid = <Number>
	C long __pid = OSgetpid();
	C Number_SetLong(_pid, __pid);
	return pid
