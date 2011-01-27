#include "internals/basics.h"
#include "internals/AutoreleasePool/interface.h"

Object Object_Create(void)
{
//	DMSG("Object Create\n");
	Object toReturn = Allocator_New(_allocator, sizeof(struct Object));
	toReturn->links = 1;
	toReturn->gid = 2803832687958515712ull;
	Object_SetComparator(toReturn, &Object_EmptyComparator);
	Object_SetDestructor(toReturn, &Object_Destroy);
	Object_SetCloner(toReturn, &Object_Retain);
	Object_SetDeepCloner(toReturn, &Object_Retain);
	toReturn->entity = Allocator_GetUndeletable(_allocator);
	return toReturn;
}

Object Object_Compare(Object _self, Object object)
{
	if(_self == object)
		return _equal;
	if(object->gid > _self->gid)
	{
		return _uncomparableLess;
	} else {
		if(object->gid < _self->gid)
		{
			return _uncomparableGreater;
		} else {
			return (_self->compare)(_self, object);
		}
	}
}

Object Object_EmptyComparator(Object _self, Object object)
{
	return _equal;
}

Object Object_Retain(Object _self)
{
	DMSGS("Object: Retain.");
	_self->links++;
	return _self;
}

Object Object_Release(Object _self)
{
	DPUSHS("Object: Release.");
#if DEBUG_MEMORY
	if((_self->links <= 0) && (_self->gid != 3814824931964230656ull))
	{
		DMSG("Object: Releasing already destroyed object.");
	}
#endif
	if(!(--(_self->links)))
	{
		DPUSHS("Object: Destroy.");
		_self->destroy(_self);
		DPOPS("Object: Destroyed.");
	}
	DPOPS("Object: Released.");
	return _self;
}

Object Object_Autorelease(Object _self)
{
	DPUSHS("Object: Autorelease.");
	AutoreleasePool_Add(_autoreleasePool, _self);
	DPOPS("Object: Autoreleased.");
	return _self;
}

Object Object_Destroy(Object _self)
{
//	DMSG("Object Destroy\n");
	Allocator_Delete(_allocator, _self->entity);
	return Allocator_Delete(_allocator, _self);
}

Object Object_Clone(Object _self)
{
	return _self->clone(_self);
}

Object Object_TempClone(Object _self)
{
//	DMSG("Object TempClone\n");
	Object toReturn = _self->clone(_self);
	Object_Autorelease(toReturn);
	return toReturn;
}

Object Object_DeepClone(Object _self)
{
	return _self->deepClone(_self);
}

Object Object_TempDeepClone(Object _self)
{
	Object toReturn = _self->deepClone(_self);
	Object_Autorelease(toReturn);
	return toReturn;
}

Object Object_SetComparator(Object _self, ObjectComparator comparator)
{
	_self->compare = comparator;
	return _self;
}

Object Object_SetCloner(Object _self, ObjectCloner cloner)
{
	_self->clone = cloner;
	return _self;
}

Object Object_SetDeepCloner(Object _self, ObjectCloner deepCloner)
{
	_self->deepClone = deepCloner;
	return _self;
}

Object Object_SetDestructor(Object _self, ObjectDestructor destructor)
{
	_self->destroy = destructor;
	return _self;
}

Object Object_Hash(Object _self)
{
	return NumberFactory_FromLong(_numberFactory, (long) (_self->entity));
}

Object Object_Is(Object _self, Object object)
{
	return (_self == object) ? _true : _false;
}
