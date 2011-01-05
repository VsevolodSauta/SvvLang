#include "internals/basics.h"
#include "internals/AutoreleasePool/imports.h"


Object AutoreleasePool_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct AutoreleasePool));
	toReturn->gid =  6558146264612776960ull;
	Object_SetComparator(toReturn, &AutoreleasePool_Compare);
	Object_SetDestructor(toReturn, &AutoreleasePool_Destroy);
	Object_SetCloner(toReturn, &AutoreleasePool_Clone);
	((AutoreleasePool) (toReturn->entity))->_stack = _nil;
	toReturn = AutoreleasePool_Init(toReturn);
	return toReturn;
}

Object AutoreleasePool_Init(Object _self)
{
	DPUSHS( "Autorelease Pool: Initing" ) 
	Object_SetReleasing(&(((AutoreleasePool) (_self->entity))->_stack), Stack_Create());
	DPOPS( "Autorelease Pool: Inited" ) 
	return _self;
}

Object AutoreleasePool_Dump(Object _self)
{
	DPUSHS( "Autorelease Pool: Dumping." ) 
	Object _ms;
	_ms = Stack_Peek((((AutoreleasePool) (_self->entity))->_stack));
	Console_WriteLnNumber(_console, List_Size((((MultiSet) (_ms->entity))->_list)));
	DPOPS( "Autorelease Pool: Dumped." ) 
	return _self;
}

Object AutoreleasePool_Depth(Object _self)
{
	DMSGS( "Autorelease Pool: Getting depth." ) 
	return List_Size((((Stack) ((((AutoreleasePool) (_self->entity))->_stack)->entity))->_list));
}

Object AutoreleasePool_PushFrame(Object _self)
{
	DPUSHS( "Autorelease Pool: Pushing frame." ) 
	Object _toPush;
	_toPush = MultiSet_Create();
	Stack_Push((((AutoreleasePool) (_self->entity))->_stack), _toPush);
	Object_Release(_toPush);
	DPOPS( "Autorelease Pool: Frame pushed." ) 
	return _self;
}

Object AutoreleasePool_PopFrame(Object _self)
{
	DPUSHS( "Autorelease Pool: Popping frame." ) 
	Object _ms;
	_ms = Stack_Peek((((AutoreleasePool) (_self->entity))->_stack));
	Stack_Pop((((AutoreleasePool) (_self->entity))->_stack));
	DPOPS( "Autorelease Pool: Frame popped." ) 
	return _self;
}

Object AutoreleasePool_Add(Object _self, Object _object)
{
	DPUSHS( "Autorelease Pool: Adding object to pool." ) 
	MultiSet_Push(Stack_Peek((((AutoreleasePool) (_self->entity))->_stack)), _object);
	Object_Release(_object);
	DPOPS( "Autorelease Pool: Object added." ) 
	return _self;
}

Object AutoreleasePool_Destroy(Object _self)
{
	DPUSHS( "Autorelease Pool: Destroying." ) 
	Object_Release((((AutoreleasePool) (_self->entity))->_stack));
	DPOPS( "Autorelease Pool: Destroyed." ) 
	return Object_Destroy(_self);
}

Object AutoreleasePool_Compare(Object _self, Object _autoreleasePool)
{
	return Object_Compare((((AutoreleasePool) (_self->entity))->_stack), (((AutoreleasePool) (_autoreleasePool->entity))->_stack));
}

Object AutoreleasePool_Clone(Object _self)
{
	return _self;
}
