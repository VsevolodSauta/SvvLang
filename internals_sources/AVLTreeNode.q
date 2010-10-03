<AVLTreeNode> <AVLTreeNode> parent <AVLTreeNode> [Retain] left <AVLTreeNode> [Retain] right <Number> [Clone] height [Retain] data

AVLTreeNode Init
	self.height = -1
	return self

AVLTreeNode Destroy
	self.data Release
	self.height Release
	self.left Release
	self.right Release
	return (self AsObject) Destroy

AVLTreeNode Clone
	toReturn = <AVLTreeNode>
	toReturn.data = self.data Retain
	toReturn.height = self.height
	if toReturn NotIsLeaf
		toReturn SetLeft (self.left TempClone)
		toReturn SetRight (self.right TempClone)
	return toReturn

AVLTreeNode <Comparation> Compare <AVLTreeNode> avlTreeNode
	candidate = self.data ? avlTreeNode.data
	if candidate != equal
		return candidate
	candidate = self.height ? avlTreeNode.height
	if candidate != equal
		return candidate
	if (self.right Hash) == (avlTreeNode.right Hash)
		return (self.left Hash) ? (avlTreeNode.left Hash)
	else
		return (self.right Hash) ? (avlTreeNode.right Hash)

AVLTreeNode SetData object
	self.data = object
	if self IsLeaf
		self.left = <AVLTreeNode>
		self.right = <AVLTreeNode>
		self.height = 0
	return self

AVLTreeNode CalculateHeightOnce (CalculateHeight)
	self.height = (self.left.height + 1) Max (self.right.height + 1)
	return self

AVLTreeNode Balance
	if self.parent IsRoot
		return self
	if self.parent.parent IsRoot
		return self
	pivot = self.parent.parent
	if ((pivot.left.height - pivot.right.height) Abs) < 2
		return self
	group1
	group2
	group3
	group4
	tempData = pivot.data Retain
	if pivot.left.height > pivot.right.height
		if pivot.left.right.height > pivot.left.left.height
			group1 = pivot.left.left
			group2 = pivot.left.right.left
			group3 = pivot.left.right.right
			group4 = pivot.right
			pivot.data = pivot.left.right.data
			pivot.left.right.data = tempData
			pivot SetRight pivot.left.right
		else
			group1 = pivot.left.left.left
			group2 = pivot.left.left.right
			group3 = pivot.left.right
			group4 = pivot.right
			pivot.data = pivot.left.data
			pivot.left.data = tempData
			pivot SetRight pivot.left
			pivot SetLeft pivot.left.left
	else
		if pivot.right.right.height > pivot.right.left.height
			group1 = pivot.left
			group2 = pivot.right.left
			group3 = pivot.right.right.left
			group4 = pivot.right.right.right
			pivot.data = pivot.right.data
			pivot.right.data = tempData
			pivot SetLeft pivot.right
			pivot SetRight pivot.right.right
		else
			group1 = pivot.left
			group2 = pivot.right.left.left
			group3 = pivot.right.left.right
			group4 = pivot.right.right
			pivot.data = pivot.right.left.data
			pivot.right.left.data = tempData
			pivot SetLeft pivot.right.left
	pivot.left SetLeft group1
	pivot.left SetRight group2
	pivot.right SetLeft group3
	pivot.right SetRight group4
	pivot.left CalculateHeight
	pivot.right CalculateHeight
	pivot CalculateHeight
	tempData Release
	return self

AVLTreeNode SetLeft <AVLTreeNode> node
	self.left = node
	node.parent = self
	return self

AVLTreeNode SetRight <AVLTreeNode> node
	self.right = node
	node.parent = self
	return self

AVLTreeNode FindNodeForObject object
	toReturn = self
	while toReturn NotIsLeaf
		if toReturn.data == object
			return toReturn
		elif toReturn.data > object
			toReturn = toReturn.left
		else
			toReturn = toReturn.right
	return toReturn

AVLTreeNode IsLeaf (IsRoot IsLeafOrRoot)
	return self.height == -1

AVLTreeNode DeleteFromTree (RemoveFromTree Delete Remove)
	node = self
	if node.left NotIsLeaf
		node = node.left
		while node NotIsLeaf
			node = node.right
		node = node.parent
		node.right Release
		node.parent SetRight node.left
	elif self.right NotIsLeaf
		node = node.right
		while node NotIsLeaf
			node = node.left
		node = node.parent
		node.left Release
		node.parent SetLeft node.right
	else
		self.left Release
		self.right Release
		self.height = -1
		self RebalanceToRoot
		return self
	nodeParent = node.parent
	tempData = node.data Retain
	node.data = self.data
	self.data = tempData
	tempData Release
	node Release
	nodeParent RebalanceToRoot
	return self

AVLTreeNode RebalanceToRoot
	node = self
	while node NotIsRoot
		node CalculateHeight
		node Balance
		node = node.parent
	return self
