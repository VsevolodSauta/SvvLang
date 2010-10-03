<AVLTree> <AVLTreeNode> root

AVLTree Init
	self.root = <AVLTreeNode> SetData nil
	self.root.height = -1
	return self

AVLTree Destroy
	self.root Release
	return (self AsObject) Release

AVLTree <Comparation> Compare <AVLTree> avlTree
	return self.root Compare avlTree.root

AVLTree Clone
	toReturn = <AVLTree>
	if toReturn.root != nil
		toReturn.root = self.root Clone
	return toReturn

AVLTree Add (+) object
	node = self.root.left FindNodeForObject object
	if node IsLeaf
		node SetData object
		node Balance
	return self

AVLTree Remove (Delete - \) object
	node = self.root.left FindNodeForObject object
	if node NotIsLeaf
		node DeleteFromTree
	return self

AVLTree AddWithComfirmation (+?)
	node = self.root.left FindNodeForObject object
	if node IsLeaf
		node SetData object
		node Balance
		return true
	else
		return false

AVLTree RemoveWithConfirmation (Delete -? \?) object
	node = self.root.left FindNodeForObject object
	if node NotIsLeaf
		node DeleteFromTree
		return true
	return false

