#include "internals/basics.h"
#include "internals/Method/interface.h"

Object Method_Create()
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_GetUndeletable(_allocator);
	toReturn->gid = 14849865630305968128ull;
	Object_SetDestructor(toReturn, &Method_Destroy);
	Object_SetComparator(toReturn, &Method_Compare);
	Object_SetCloner(toReturn, &Method_Clone);
	Object_SetDeepCloner(toReturn, &Method_Clone);
	return toReturn;
}

Object Method_Compare(Object _self, Object _method)
{
	if(((long) (_self->entity)) > ((long) (_method->entity)))
	{
		return _greater;
	}
	if(((long) (_self->entity)) < ((long) (_method->entity)))
	{
		return _less;
	}
	return _equal;
}

Object Method_Clone(Object _self)
{
	Object toReturn = Method_Create();
	toReturn->entity = _self->entity;
	return toReturn;
}

Object Method_Destroy(Object _self)
{
	_self->entity = Allocator_GetUndeletable(_allocator);
	return Object_Destroy(_self);
}
