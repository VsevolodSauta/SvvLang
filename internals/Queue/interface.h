typedef struct Queue {
	Object _list;
} *Queue;

Object Queue_Create(void);
Object Queue_Init(Object _self);
Object Queue_Push(Object _self, Object _object);
Object Queue_Pop(Object _self);
Object Queue_PopIfNotEmpty(Object _self);
Object Queue_Remove(Object _self);
Object Queue_RemoveIfNotEmpty(Object _self);
Object Queue_Peek(Object _self);
Object Queue_Empty(Object _self);
Object Queue_Compare(Object _self, Object _queue);
Object Queue_Destroy(Object _self);
Object Queue_GetList(Object _self);
Object Queue_Clone(Object _self);
Object Queue_DeepClone(Object _self);
