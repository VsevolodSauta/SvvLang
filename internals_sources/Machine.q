<Machine> placeHolder

Machine Init
	allocator = <Allocator>
	nothing = null = nil = <Undestroyable>
	less = <Undestroyable>
	greater = <Undestroyable>
	equal = <Undestroyable>
	uncomparableLess = <Undestroyable>
	uncomparableGreater = <Undestroyable>
	true = yes = <Undestroyable>
	false = no = <Undestroyable>
	stringFactory = <Undestroyable>
	numberFactory = <Undestroyable>
	logicFactory = <Undestroyable>
	autoreleasePool = <AutoreleasePool>
	return self

Machine Destroy
	return self Destroy

Machine Clone
	return self

Machine <Comparation> Compare <Machine> machine
	return equal

