<AutoreleasePool> <Stack> [Retain] stack

AutoreleasePool Init
	DEBUG_PUSH ("Autorelease Pool: Initing")
	self.stack = <Stack>
	DEBUG_POP ("Autorelease Pool: Inited")
	return self

AutoreleasePool Dump
	DEBUG_PUSH ("Autorelease Pool: Dumping.")
	ms = (self.stack Peek) AsMultiSet
	console PrintLnNumber (ms.list Size)
	DEBUG_POP ("Autorelease Pool: Dumped.")
	return self

AutoreleasePool Depth
	DEBUG_MSG ("Autorelease Pool: Getting depth.")
	return (self.stack.list Size)

AutoreleasePool PushFrame (++)
	DEBUG_PUSH ("Autorelease Pool: Pushing frame.")
	toPush = <MultiSet>
	self.stack Push toPush
	toPush Release
	DEBUG_POP ("Autorelease Pool: Frame pushed.")
	return self

AutoreleasePool PopFrame (--)
	DEBUG_PUSH ("Autorelease Pool: Popping frame.")
	ms = (self.stack Peek) AsMultiSet
	(self.stack Pop)
	DEBUG_POP ("Autorelease Pool: Frame popped.")
	return self

AutoreleasePool Add object
	DEBUG_PUSH ("Autorelease Pool: Adding object to pool.")
	((self.stack Peek) AsMultiSet) Push object
	object Release
	DEBUG_POP ("Autorelease Pool: Object added.")
	return self

AutoreleasePool <Object> Destroy
	DEBUG_PUSH ("Autorelease Pool: Destroying.")
	self.stack Release
	DEBUG_POP ("Autorelease Pool: Destroyed.")
	return (self AsObject) Destroy

AutoreleasePool <Comparation> Compare <AutoreleasePool> autoreleasePool
	return self.stack Compare autoreleasePool.stack					// Nobody needs this method

AutoreleasePool Clone
	return self									// Nobody needs this method
