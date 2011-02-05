#include "internals/basics.h"
#include "internals/AutoreleasePool/imports.h"


Object AutoreleasePool_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("AutoreleasePool: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct AutoreleasePool));
	_self->gid =  6558146264612776960ull;
	Object_SetComparator(_self, &AutoreleasePool_Compare);
	Object_SetDestructor(_self, &AutoreleasePool_Destroy);
	Object_SetCloner(_self, &AutoreleasePool_Clone);
	Object_SetDeepCloner(_self, &AutoreleasePool_DeepClone);
	((AutoreleasePool) (_self->entity))->_stack = _nil;
	_self = AutoreleasePool_Init(_self);
	DPOPS ("AutoreleasePool: Create ended.")
	return _self;
}

Object AutoreleasePool_Init(Object _self)
{
	DPUSHS ("AutoreleasePool: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object_SetReleasing(&(((AutoreleasePool) (_self->entity))->_stack), Stack_Create());
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: Init ended.")
	return toReturn;
}

Object AutoreleasePool_Dump(Object _self)
{
	DPUSHS ("AutoreleasePool: Dump begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object _list;
	_list = Stack_Peek((((AutoreleasePool) (_self->entity))->_stack));
	Console_WriteLnNumber(_console, List_Size(_list));
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: Dump ended.")
	return toReturn;
}

Object AutoreleasePool_Depth(Object _self)
{
	DPUSHS ("AutoreleasePool: Depth begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object toReturn = List_Size((((Stack) ((((AutoreleasePool) (_self->entity))->_stack)->entity))->_list));
	DPOPS ("AutoreleasePool: Depth ended.")
	return toReturn;
}

Object AutoreleasePool_PushFrame(Object _self)
{
	DPUSHS ("AutoreleasePool: PushFrame begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object _toPush;
	_toPush = List_Create();
	Stack_Push((((AutoreleasePool) (_self->entity))->_stack), _toPush);
	Object_Release(_toPush);
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: PushFrame ended.")
	return toReturn;
}

Object AutoreleasePool_PopFrame(Object _self)
{
	DPUSHS ("AutoreleasePool: PopFrame begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Stack_Remove((((AutoreleasePool) (_self->entity))->_stack));
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: PopFrame ended.")
	return toReturn;
}

Object AutoreleasePool_Add(Object _self, Object _object)
{
	DPUSHS ("AutoreleasePool: Add begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	List_PushBack(Stack_Peek((((AutoreleasePool) (_self->entity))->_stack)), _object);
	Object_Release(_object);
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: Add ended.")
	return toReturn;
}

Object AutoreleasePool_Destroy(Object _self)
{
	DPUSHS ("AutoreleasePool: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object_Release((((AutoreleasePool) (_self->entity))->_stack));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("AutoreleasePool: Destroy ended.")
	return toReturn;
}

Object AutoreleasePool_Compare(Object _self, Object _autoreleasePool)
{
	DPUSHS ("AutoreleasePool: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object toReturn = Object_Compare((((AutoreleasePool) (_self->entity))->_stack), (((AutoreleasePool) (_autoreleasePool->entity))->_stack));
	DPOPS ("AutoreleasePool: Compare ended.")
	return toReturn;
}

Object AutoreleasePool_Clone(Object _self)
{
	DPUSHS ("AutoreleasePool: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: Clone ended.")
	return toReturn;
}

Object AutoreleasePool_DeepClone(Object _self)
{
	DPUSHS ("AutoreleasePool: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6558146264612776960ull )
	Object toReturn = _self;
	DPOPS ("AutoreleasePool: DeepClone ended.")
	return toReturn;
}
