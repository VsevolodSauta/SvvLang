#include "internals/basics.h"
#include "internals/ListMap/imports.h"


Object ListMap_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListMap: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListMap));
	_self->gid =  2108332898258556672ull;
	Object_SetComparator(_self, &ListMap_Compare);
	Object_SetDestructor(_self, &ListMap_Destroy);
	Object_SetCloner(_self, &ListMap_Clone);
	Object_SetDeepCloner(_self, &ListMap_DeepClone);
	((ListMap) (_self->entity))->_root = _nil;
	_self = ListMap_Init(_self);
	DPOPS ("ListMap: Create ended.")
	return _self;
}

Object ListMap_Init(Object _self)
{
	DPUSHS ("ListMap: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2108332898258556672ull )
	(((ListMap) (_self->entity))->_root) = ListMapNode_Create();
