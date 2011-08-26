<Runtime> placeHolder

Runtime Init
	nothing = null = nil = <Undestroyable>
	less = <Comparison>
	greater = <Comparison>
	equal = <Comparison>
	uncomparableLess = <Comparison>
	uncomparableGreater = <Comparison>
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
	superClass = <SuperClass>
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

Runtime <Comparison> Compare <Runtime> runtime
	return equal
