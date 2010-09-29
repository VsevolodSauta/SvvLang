typedef struct Stack {
	Object list;
} *Stack;

Object Stack_Create(void);
Object Stack_Init(Object self);
Object Stack_Push(Object self, Object object);
Object Stack_Pop(Object self);
Object Stack_Peek(Object self);
Object Stack_Compare(Object self, Object queue);
Object Stack_Destroy(Object self);
Object Stack_GetList(Object self);
Object Stack_Clone(Object self);
