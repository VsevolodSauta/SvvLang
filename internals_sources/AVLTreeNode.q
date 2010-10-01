<AVLTreeNode> <AVLTreeNode> parent <AVLTreeNode> left <AVLTreeNode> right <Number> height data

AVLTreeNode Init
	self.left = nil
	self.right = nil
	self.height = -1 Retain
	self.data = nil
	self.parent = nil
	return self

AVLTreeNode Destroy
	self.data Release
	self.height Release
	self.left Release
	self.right Release
	return (self AsObject) Destroy

AVLTreeNode Clone (DeepClone)
	toReturn = <AVLTreeNode>
	toReturn.data = self.data Retain
	toReturn.height = self.height Clone
	if toReturn NotIsLeaf
		toReturn.left = self.left DeepClone
		toReturn.left.parent = toReturn
		toReturn.right = self.left DeepClone
		toReturn.right.parent = toReturn
	return toReturn

AVLTreeNode <Comparation> Compare <AVLTreeNode> avlTreeNode
	candidate = self.data ? avlTreeNode.data
	if candidate != equal
		return candidate
	candidate = self.height ? avlTreeNode.data
	if candidate != equal
		return candidate
	if (self.right Hash) == (avlTreeNode.right Hash)
		return (self.left Hash) Compare (avlTreeNode.left Hash)
	else
		return (self.right Hash) Compare (avlTreeNode.right Hash)

AVLTreeNode SetData object
	toRelease = self.data
	self.data = object Retain
	if self IsLeaf
		self.left = <AVLTreeNode>
		self.right = <AVLTreeNode>
		self.height = 0
	else
		toRelease Release
	return self

AVLTreeNode CalculateHeight
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
	if pivot.left.height > pivot.right.height
		if pivot.left.right.height > pivot.left.left.height
			group1 = pivot.left.left
			group2 = pivot.left.right.left
			group3 = pivot.left.right.right
			group4 = pivot.right
			tempData = pivot.data
			pivot.data = pivot.left.right.data
			pivot.left.right.data = tempData
			pivot SetRight pivot.left.right
		else
			group1 = pivot.left.left.left
			group2 = pivot.left.left.right
			group3 = pivot.left.right
			group4 = pivot.right
			tempData = pivot.data
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
			tempData = pivot.data
			pivot.data = pivot.right.data
			pivot.right.data = tempData
			pivot SetLeft pivot.right
			pivot SetRight pivot.right.right
		else
			group1 = pivot.left
			group2 = pivot.right.left.left
			group3 = pivot.right.left.right
			group4 = pivot.right.right
			tempData = pivot.data
			pivot.data = pivot.right.left.data
			pivot.right.left.data = tempData
			pivot SetLeft pivot.right.left
	pivot.left SetLeft group1
	pivot.left SetRight group2
	pivot.right SetLeft group3
	pivot.right SetRight group4
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

AVLTreeNode IsLeaf (IsRoot IsLeafOrRoot IsInUse)
	return self.height == -1


