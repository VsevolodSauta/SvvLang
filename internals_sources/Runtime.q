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
	json = <JSON>
	return self

Runtime Destroy
	autoreleasePool Release
	console Release
	json Release
	return self Destroy

Runtime Clone
	return self

Runtime DeepClone
	return self

Runtime <Comparation> Compare <Runtime> runtime
	return equal
