<AutoreleasePool> <Stack> [Retain] stack

AutoreleasePool Init
	self.stack = <Stack>
	return self

AutoreleasePool Dump
	list = (self.stack Peek) AsList
	console PrintLnNumber (list Size)
	return self

AutoreleasePool Depth
	return (self.stack.list Size)

AutoreleasePool PushFrame (++)
	toPush = <List>
	self.stack Push toPush
	toPush Release
	return self

AutoreleasePool PopFrame (--)
	(self.stack Remove)
	return self

AutoreleasePool Add object
	((self.stack Peek) AsList) Push object
	object Release
	return self

AutoreleasePool Destroy
	self.stack Release
	return self Destroy

AutoreleasePool <Comparison> Compare <AutoreleasePool> autoreleasePool
	return self.stack ? autoreleasePool.stack					// Nobody really needs this method

AutoreleasePool Clone
	return self									// Nobody needs this method

AutoreleasePool DeepClone
	return self									// Nobody needs this method
