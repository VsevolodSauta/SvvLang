typedef struct AVLTree {
	Object _root;
} *AVLTree;

Object AVLTree_Create(void);
Object AVLTree_Init(Object _self);
Object AVLTree_Destroy(Object _self);
Object AVLTree_Compare(Object _self, Object _avlTree);
Object AVLTree_Clone(Object _self);
Object AVLTree_Add(Object _self, Object _object);
