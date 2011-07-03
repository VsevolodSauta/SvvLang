#include "internals/basics.h"
#include "internals/Thread/imports.h"


Object Thread_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Thread: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Thread));
	_self->gid =  2248413717759836160ull;
	Object_SetComparator(_self, &Thread_Compare);
	Object_SetDestructor(_self, &Thread_Destroy);
	Object_SetCloner(_self, &Thread_Clone);
	Object_SetDeepCloner(_self, &Thread_DeepClone);
	((Thread) (_self->entity))->_pid = _nil;
	((Thread) (_self->entity))->_autoreleasePool = _nil;
	_self = Thread_Init(_self);
	DPOPS ("Thread: Create ended.")
	return _self;
}

Object Thread_Init(Object _self)
{
	DPUSHS ("Thread: Init begined.")
	ASSERT_C ( "Thread:Init --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	(((Thread) (_self->entity))->_autoreleasePool) = AutoreleasePool_Create();
	AutoreleasePool_PushFrame((((Thread) (_self->entity))->_autoreleasePool));
	Object toReturn = _self;
	DPOPS ("Thread: Init ended.")
	return toReturn;
}

Object Thread_SetPid(Object _self, Object _pid)
{
	DPUSHS ("Thread: SetPid begined.")
	ASSERT_C ( "Thread:SetPid --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	ASSERT_C ( "Thread:SetPid --- Checking for correct parameter type failed at parameter _pid.", _pid->gid == 15425740279749906432ull || _pid == _nil )
	Object_SetRetaining(&(((Thread) (_self->entity))->_pid), _pid);
	Object toReturn = _self;
	DPOPS ("Thread: SetPid ended.")
	return toReturn;
}

Object Thread_Clone(Object _self)
{
	DPUSHS ("Thread: Clone begined.")
	ASSERT_C ( "Thread:Clone --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("Thread: Clone ended.")
	return toReturn;
}

Object Thread_DeepClone(Object _self)
{
	DPUSHS ("Thread: DeepClone begined.")
	ASSERT_C ( "Thread:DeepClone --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("Thread: DeepClone ended.")
	return toReturn;
}

Object Thread_Compare(Object _self, Object _thread)
{
	DPUSHS ("Thread: Compare begined.")
	ASSERT_C ( "Thread:Compare --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	ASSERT_C ( "Thread:Compare --- Checking for correct parameter type failed at parameter _thread.", _thread->gid ==  2248413717759836160ull || _thread == _nil )
	Object toReturn = Object_Compare((((Thread) (_self->entity))->_pid), (((Thread) (_thread->entity))->_pid));
	DPOPS ("Thread: Compare ended.")
	return toReturn;
}

Object Thread_Destroy(Object _self)
{
	DPUSHS ("Thread: Destroy begined.")
	ASSERT_C ( "Thread:Destroy --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	Object_Release((((Thread) (_self->entity))->_pid));
	Object_Release((((Thread) (_self->entity))->_autoreleasePool));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Thread: Destroy ended.")
	return toReturn;
}

Object Thread_AutoreleasePool(Object _self)
{
	DPUSHS ("Thread: AutoreleasePool begined.")
	ASSERT_C ( "Thread:AutoreleasePool --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	Object toReturn = (((Thread) (_self->entity))->_autoreleasePool);
	DPOPS ("Thread: AutoreleasePool ended.")
	return toReturn;
}

Object Thread_Pid(Object _self)
{
	DPUSHS ("Thread: Pid begined.")
	ASSERT_C ( "Thread:Pid --- Checking for correct object type failed.", _self->gid ==  2248413717759836160ull )
	Object toReturn = (((Thread) (_self->entity))->_pid);
	DPOPS ("Thread: Pid ended.")
	return toReturn;
}
