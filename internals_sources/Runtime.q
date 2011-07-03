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
	threadManager = <ThreadManager>
	threadManager RegisterCurrentThread
	console = <Console>
	jsonParser = <JSONParser>
	entitiesFactory = <ExternalEntitiesFactory>
	return self

Runtime Destroy
	threadManager Release
	console Release
	jsonParser Release
	return self Destroy

Runtime Clone
	return self

Runtime DeepClone
	return self

Runtime <Comparation> Compare <Runtime> runtime
	return equal
