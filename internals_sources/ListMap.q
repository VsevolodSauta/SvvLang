<ListMap> <ListMapNode> [Constant] root

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

ListMap Add (AtPut Put +) <List> list object
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			next = <ListMapNode>
			node.nextMap AtPut (iterator ThisData) next
			node = next
		iterator ++
	node.mapped = true
	node.mapping = object
	return self

ListMap RemoveKey (DeleteKey - \) <List> list
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return self
		iterator ++
	node.mapped = false
	node.mapping = nil
	return self

ListMap <Logic> RemoveKeyWithConfirmation (DeleteKeyWithConfirmation -? \?) <List> list
	iterator = list First
	node = self.root
	while iterator NotThisEnd
		if node.nextMap HasKey (iterator ThisData)
			node = (node.nextMap GetValueForKey (iterator ThisData)) AsListMapNode
		else
			return false
		iterator ++
	node.mapped = false
	node.mapping = nil
	return true

ListMap <Object> GetAt (AtGet GetValueForKey Get) <List> list
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
