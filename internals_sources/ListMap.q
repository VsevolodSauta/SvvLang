<ListMap> <ListMapNode> root

ListMap Init
	self.root = <ListMapNode>
	return self

ListMap <Comparation> Compare <ListMap> listSet
	return self.root ? listSet.root

ListMap Destroy
	self.root Release
	return self Destroy

ListMap Clone
	toReturn = <ListMap>
	toReturn.root Release
	toReturn.root = self.root Clone
	return toReturn

ListMap DeepClone
	toReturn = <ListMap>
	toReturn.root Release
	toReturn.root = self.root DeepClone
	return toReturn

ListMap <Logic> Empty
	return (self.root.mapped Not) And (self.root.nextMap Empty)

ListMap Add (AtPut Put +) <List> list object
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			next = <ListMapNode>
			node.nextMap AtPut (iterator ThisData) next
			next Release
			node = next
		iterator ++
	node.mapped = true
	node.mapping = object
	return self

ListMap AddListMap (Merge MergeStrong) <ListMap> listMap
	self.root MergeRecursiveStrong listMap.root
	return self

ListMap Remove (RemoveAt RemoveKey Remove DeleteKey Delete - \) <List> list
	self RemoveKeyWithConfirmation list
	return self

ListMap RemoveAll
	self.root = <ListMapNode>
	return self

ListMap <Logic> RemoveKeyWithConfirmation (RemoveWithConfirmation DeleteKeyWithConfirmation DeleteWithConfirmation -? \?) <List> list
	stack = <Stack>
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			stack Push node
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			stack Release
			return false
		iterator ++
	stack Push node
	node.mapped = false
	node.mapping = nil
	while (stack NotEmpty) And (iterator NotPrevBegin)
		node = (stack Pop) AsListMapNode
		iterator --
		if ((node.nextMap Size) != 0) Or (node.mapped)
			break
		else
			node Release
			parent = ((stack Peek) AsListMapNode)
			parent.nextMap RemoveKey (iterator ThisData)
	stack Release
	return true

ListMap <Object> ObjectAt (AtGet GetValueForKey At GetAt) <List> list
	node = self.root
	iterator = list First
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return nil
		iterator ++
	if node.mapped
		return node.mapping
	else
		return nil

ListMap <Logic> Contains (HasKey Has) <List> list
	node = self.root
	iterator = list First
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return false
		iterator ++
	return node.mapped

ListMap <ListMap> ListMapAt <List> list
	return (self GetAt list) AsListMap

ListMap <List> ListAt <List> list
	return (self GetAt list) AsList

ListMap <Queue> QueueAt <List> list
	return (self GetAt list) AsQueue

ListMap <Logic> LogicAt <List> list
	return (self GetAt list) AsLogic

ListMap <Number> NumberAt <List> list
	return (self GetAt list) AsNumber

ListMap <Synonim> SynonimAt <List> list
	return (self GetAt list) AsSynonim

ListMap <Method> MethodAt <List> list
	return (self GetAt list) AsMethod

ListMap <ListMapIterator> First
	iterator = <ListMapIterator>
	iterator SetListMap self
	iterator ToBegin
	return iterator Autorelease

ListMap <ListMapIterator> Last
	iterator = <ListMapIterator>
	iterator SetListMap self
	iterator ToEnd
	return iterator Autorelease
	
ListMap DumpKeys
	iterator = self First
	while iterator NotThisEnd
		console PrintLnString (iterator Key)
		iterator ++
	return self