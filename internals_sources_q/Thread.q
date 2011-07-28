<Thread> <Number> [Retain] pid <AutoreleasePool> autoreleasePool

Thread Init
	self.autoreleasePool = <AutoreleasePool>
	self.autoreleasePool ++
	return self

Thread SetPid <Number> pid
	self.pid = pid
	return self

Thread Clone
	return self Retain

Thread DeepClone
	return self Retain

Thread <Comparison> Compare <Thread> thread
	return self.pid ? thread.pid

Thread Destroy
	self.pid Release
	self.autoreleasePool Release
	return self Destroy

Thread <AutoreleasePool> AutoreleasePool
	return self.autoreleasePool

Thread <Number> Pid
	return self.pid
