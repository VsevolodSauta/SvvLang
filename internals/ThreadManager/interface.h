typedef struct ThreadManager {
	Object _threadsByPidMap;
} *ThreadManager;

Object ThreadManager_Create(void);
Object ThreadManager_Init(Object _self);
Object ThreadManager_Clone(Object _self);
Object ThreadManager_DeepClone(Object _self);
Object ThreadManager_Compare(Object _self, Object _tm);
Object ThreadManager_Destroy(Object _self);
Object ThreadManager_RegisterCurrentThread(Object _self);
Object ThreadManager_RegisterThread(Object _self, Object _thread);
Object ThreadManager_AutoreleasePool(Object _self);
Object ThreadManager_SpawnThreadWithMethodAndEntity(Object _self, Object _method, Object _entity);
Object ThreadManager_Pid(Object _self);
