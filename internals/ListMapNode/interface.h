typedef struct ListMapNode {
	Object _nextMap;
	Object _mapped;
	Object _mapping;
} *ListMapNode;

Object ListMapNode_Create(void);
Object ListMapNode_Init(Object _self);
Object ListMapNode_Destroy(Object _self);
Object ListMapNode_Clone(Object _self);
Object ListMapNode_Compare(Object _self, Object _listMapNode);
