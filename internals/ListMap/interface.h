typedef struct ListMap {
	Object _root;
} *ListMap;

Object ListMap_Create(void);
Object ListMap_Init(Object _self);
