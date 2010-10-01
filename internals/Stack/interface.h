typedef struct Stack {
	Object _list;
} *Stack;

Object Stack_Create(void);
Object Stack_Init(Object _self);
Object Stack_Push(Object _self, Object _object);
Object Stack_Pop(Object _self);
Object Stack_Peek(Object _self);
Object Stack_Compare(Object _self, Object _queue);
Object Stack_Destroy(Object _self);
Object Stack_GetList(Object _self);
Object Stack_Clone(Object _self);
