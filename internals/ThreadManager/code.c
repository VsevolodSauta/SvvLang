#include "internals/basics.h"
#include "internals/ThreadManager/imports.h"


Object ThreadManager_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ThreadManager: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ThreadManager));
	_self->gid =  8077187921755639808ull;
	Object_SetComparator(_self, &ThreadManager_Compare);
	Object_SetDestructor(_self, &ThreadManager_Destroy);
	Object_SetCloner(_self, &ThreadManager_Clone);
	Object_SetDeepCloner(_self, &ThreadManager_DeepClone);
	((ThreadManager) (_self->entity))->_threadsByPidMap = _nil;
	_self = ThreadManager_Init(_self);
	DPOPS ("ThreadManager: Create ended.")
	return _self;
}

Object ThreadManager_Init(Object _self)
{
	DPUSHS ("ThreadManager: Init begined.")
	ASSERT_C ( "ThreadManager:Init --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	(((ThreadManager) (_self->entity))->_threadsByPidMap) = Map_Create();
	Object toReturn = _self;
	DPOPS ("ThreadManager: Init ended.")
	return toReturn;
}

Object ThreadManager_Clone(Object _self)
{
	DPUSHS ("ThreadManager: Clone begined.")
	ASSERT_C ( "ThreadManager:Clone --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ThreadManager: Clone ended.")
	return toReturn;
}

Object ThreadManager_DeepClone(Object _self)
{
	DPUSHS ("ThreadManager: DeepClone begined.")
	ASSERT_C ( "ThreadManager:DeepClone --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ThreadManager: DeepClone ended.")
	return toReturn;
}

Object ThreadManager_Compare(Object _self, Object _tm)
{
	DPUSHS ("ThreadManager: Compare begined.")
	ASSERT_C ( "ThreadManager:Compare --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	ASSERT_C ( "ThreadManager:Compare --- Checking for correct parameter type failed at parameter _tm.", _tm->gid ==  8077187921755639808ull || _tm == _nil )
	Object toReturn = Object_Compare(Object_Hash(_self), Object_Hash(_tm));
	DPOPS ("ThreadManager: Compare ended.")
	return toReturn;
}

Object ThreadManager_Destroy(Object _self)
{
	DPUSHS ("ThreadManager: Destroy begined.")
	ASSERT_C ( "ThreadManager:Destroy --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object_Release((((ThreadManager) (_self->entity))->_threadsByPidMap));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ThreadManager: Destroy ended.")
	return toReturn;
}

Object ThreadManager_RegisterCurrentThread(Object _self)
{
	DPUSHS ("ThreadManager: RegisterCurrentThread begined.")
	ASSERT_C ( "ThreadManager:RegisterCurrentThread --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object _pid;
	_pid = ThreadManager_Pid(_self);
	if((Logic_Not(Map_ContainsKey((((ThreadManager) (_self->entity))->_threadsByPidMap), _pid))) != _false)
	{
		Object _thread;
		_thread = Thread_Create();
		Thread_SetPid(_thread, _pid);
		Map_Add((((ThreadManager) (_self->entity))->_threadsByPidMap), _pid, _thread);
	}
	Object_Release(_pid);
	Object toReturn = _self;
	DPOPS ("ThreadManager: RegisterCurrentThread ended.")
	return toReturn;
}

Object ThreadManager_RegisterThread(Object _self, Object _thread)
{
	DPUSHS ("ThreadManager: RegisterThread begined.")
	ASSERT_C ( "ThreadManager:RegisterThread --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	ASSERT_C ( "ThreadManager:RegisterThread --- Checking for correct parameter type failed at parameter _thread.", _thread->gid ==  2248413717759836160ull || _thread == _nil )
	Object _pid;
	_pid = (((Thread) (_thread->entity))->_pid);
	if((Logic_Not(Map_ContainsKey((((ThreadManager) (_self->entity))->_threadsByPidMap), _pid))) != _false)
	{
		Map_Add((((ThreadManager) (_self->entity))->_threadsByPidMap), _pid, _thread);
	}
	Object toReturn = _self;
	DPOPS ("ThreadManager: RegisterThread ended.")
	return toReturn;
}

Object ThreadManager_AutoreleasePool(Object _self)
{
	DPUSHS ("ThreadManager: AutoreleasePool begined.")
	ASSERT_C ( "ThreadManager:AutoreleasePool --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object _pid;
	_pid = ThreadManager_Pid(_self);
	Object _autoreleasePool;
	_autoreleasePool = Thread_AutoreleasePool(Map_GetValueForKey((((ThreadManager) (_self->entity))->_threadsByPidMap), _pid));
	Object_Release(_pid);
	Object toReturn = _autoreleasePool;
	DPOPS ("ThreadManager: AutoreleasePool ended.")
	return toReturn;
}

Object ThreadManager_SpawnThreadWithMethodAndEntity(Object _self, Object _method, Object _entity)
{
	DPUSHS ("ThreadManager: SpawnThreadWithMethodAndEntity begined.")
	ASSERT_C ( "ThreadManager:SpawnThreadWithMethodAndEntity --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	ASSERT_C ( "ThreadManager:SpawnThreadWithMethodAndEntity --- Checking for correct parameter type failed at parameter _method.", _method->gid == 14849865630305968128ull || _method == _nil )
	OSclone ( 0xf11, _method->entity, _entity ) ; 
	Object toReturn = _self;
	DPOPS ("ThreadManager: SpawnThreadWithMethodAndEntity ended.")
	return toReturn;
}

Object ThreadManager_Pid(Object _self)
{
	DPUSHS ("ThreadManager: Pid begined.")
	ASSERT_C ( "ThreadManager:Pid --- Checking for correct object type failed.", _self->gid ==  8077187921755639808ull )
	Object _pid;
	_pid = Number_Create();
	long __pid = OSgetpid ( ) ; 
	Number_SetLong ( _pid, __pid ) ; 
	Object toReturn = _pid;
	DPOPS ("ThreadManager: Pid ended.")
	return toReturn;
}
