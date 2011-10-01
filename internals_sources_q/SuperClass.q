<SuperClass@Object> <Map> classForGid <ListMap> methodsForClass <ListMap> parentClassForClass

@superClass

SuperClass Init
	self.methodsForClass = <ListMap>
	self.parentClassForClass = <ListMap>
	self.classForGid = <Map>
	return self

SuperClass Destroy
	self.methodsForClass Release
	self.parentClassForClass Release
	self.classForGid Release
	return super Destroy

SuperClass Register Class With Name <List> className With GID <Number> gid With Parent Class Name <List> parentClassName
	emptyDispatchTable = <ListMap>
	self.methodsForClass At className Put emptyDispatchTable
	emptyDispatchTable Release
	if (parentClassName Is nil) Not
		self.parentClassForClass At className Put parentClassName
	self.classForGid At gid Put className
	return self

SuperClass Register Method <Method> method With Name <List> methodName For Class With Name <List> className
	(self.methodsForClass ListMapAt className) AtPut methodName method
	return self

SuperClass <List> Class Name For GID <Number> gid
	return self.classForGid At gid

SuperClass <Method> Method With Name <List> methodName In Class With Name <List> className
	return (self.methodsForClass ListMapAt className) At className

SuperClass <List> Parent Class Name For Class With Name <List> className
	return self.parentClassForClass At className
