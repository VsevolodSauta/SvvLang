<Thread@Object> <Number> [Retain] pid <AutoreleasePool> autoreleasePool

Thread Init
	self.autoreleasePool = <AutoreleasePool>
	self.autoreleasePool ++
	return self

Thread SetPid <Number> pid
	self.pid = pid
	return self

Thread <Comparison> CompareSameGID <Thread> thread
	return self.pid ? thread.pid

Thread Destroy
	self.pid Release
	self.autoreleasePool Release
	return super Destroy

Thread <AutoreleasePool> AutoreleasePool
	return self.autoreleasePool

Thread <Number> Pid
	return self.pid
