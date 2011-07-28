<SuperClass> <ListMap> classes

@superClass

SuperClass Init
	self.classes = <ListMap>
	return self

SuperClass Clone
	return self Retain

SuperClass DeepClone
	return self Retain

SuperClass Destroy
	self.classes Release
	return self Destroy

SuperClass <Comparison> Compare <SuperClass> _superClass
	return equal

SuperClass RegisterClass <List> className
	emptyDispatchTable = <ListMap>
	self.classes AtPut className emptyDispatchTable
	emptyDispatchTable Release
	return self

SuperClass RegisterMethodWithNameForClass <Method> method <List> methodName <List> className
	(self.classes ListMapAt className) AtPut methodName method
	return self
