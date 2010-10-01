<AVLTree> <AVLTreeNode> root

AVLTree Init
	self.root = <AVLTreeNode> SetData nil
	return self

AVLTree Destroy
	self.root Release
	return (self AsObject) Release

AVLTree <Comparation> Compare <AVLTree> avlTree
	return self.root Compare avlTree.root

AVLTree Clone
	toReturn = <AVLTree>
	if toReturn.root != nil
		toReturn.root = self.root DeepClone
	return toReturn

AVLTree Add object
	node = self.root.left FindNodeForObject object
	if node IsLeaf
		node SetData object
		node Balance
	return self


