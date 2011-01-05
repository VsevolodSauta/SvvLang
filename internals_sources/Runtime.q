<Runtime> placeHolder

Runtime Init
	nothing = null = nil = <Undestroyable>
	less = <Comparation>
	greater = <Comparation>
	equal = <Comparation>
	uncomparableLess = <Comparation>
	uncomparableGreater = <Comparation>
	true = yes = <Logic>
	false = no = <Logic>
	stringFactory = <StringFactory>
	numberFactory = <NumberFactory>
	logicFactory = <LogicFactory>
	autoreleasePool = <AutoreleasePool>
	autoreleasePool PushFrame
	console = <Console>
	return self

Runtime Destroy
	DEBUG_PUSH ("Runtime: Destroying.")
	autoreleasePool Release
	DEBUG_POP ("Runtime: Destroyed.")
	return self Destroy

Runtime Clone
	return self

Runtime <Comparation> Compare <Runtime> runtime
	return equal

