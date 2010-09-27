typedef struct Queue {
	Object list;
} *Queue;
Object Queue_Create(void);
Object Queue_Init(Object self);
Object Queue_Push(Object self, Object object);
Object Queue_Pop(Object self);
Object Queue_Peek(Object self);
Object Queue_Compare(Object self, Object queue);
Object Queue_Destroy(Object self);
Object Queue_GetList(Object self);
Object Queue_Clone(Object self);
