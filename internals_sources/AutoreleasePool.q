<AutoreleasePool> <Stack> stack

AutoreleasePool Init
	self.stack = <Stack>
	return self

AutoreleasePool PushFrame
	self.stack Push <MultiSet>
	return self

AutoreleasePool PopFrame object
	(self.stack Pop) Release
	return self

AutoreleasePool Add object
	((self.stack Peek) AsMultiSet) Push object
	object Release
	return self

AutoreleasePool <Object> Destroy
	self.stack Release
	return (self AsObject) Destroy

AutoreleasePool <Comparation> Compare <AutoreleasePool> autoreleasePool
	return (self.stack Hash) Compare (autoreleasePool.stack Hash)			// Nobody needs this function

AutoreleasePool Clone
	return <AutoreleasePool>							// Nobody needs this function

