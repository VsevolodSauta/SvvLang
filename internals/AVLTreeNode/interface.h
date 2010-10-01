typedef struct AVLTreeNode {
	Object _parent;
	Object _left;
	Object _right;
	Object _height;
	Object _data;
} *AVLTreeNode;

Object AVLTreeNode_Create(void);
Object AVLTreeNode_Init(Object _self);
Object AVLTreeNode_Destroy(Object _self);
Object AVLTreeNode_Clone(Object _self);
Object AVLTreeNode_Compare(Object _self, Object _avlTreeNode);
Object AVLTreeNode_SetData(Object _self, Object _object);
Object AVLTreeNode_CalculateHeight(Object _self);
Object AVLTreeNode_Balance(Object _self);
Object AVLTreeNode_SetLeft(Object _self, Object _node);
Object AVLTreeNode_SetRight(Object _self, Object _node);
Object AVLTreeNode_FindNodeForObject(Object _self, Object _object);
Object AVLTreeNode_IsLeaf(Object _self);
