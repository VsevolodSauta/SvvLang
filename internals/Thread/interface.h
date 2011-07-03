typedef struct Thread {
	Object _pid;
	Object _autoreleasePool;
} *Thread;

Object Thread_Create(void);
Object Thread_Init(Object _self);
Object Thread_SetPid(Object _self, Object _pid);
Object Thread_Clone(Object _self);
Object Thread_DeepClone(Object _self);
Object Thread_Compare(Object _self, Object _thread);
Object Thread_Destroy(Object _self);
Object Thread_AutoreleasePool(Object _self);
Object Thread_Pid(Object _self);
