#include "internals/basics.h"
#include "internals/ThreadManager/interface.h"
#include "internals/AutoreleasePool/interface.h"
#include "internals/Logic/interface.h"
#include "internals/ListMap/interface.h"
#include "internals/Comparison/interface.h"
#include "internals/SuperClass/interface.h"

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
	asm volatile (
		"lock\n"
		"xadd %1, %0\n"
		: "=m" (_self->links)
		: "r" (1)
	);
	return _self;
}

Object Object_Release(Object _self)
{
	DPUSHS("Object: Release.");
	
	register int toAdd = -1;
	asm volatile (
		"lock\n"
		"xadd %1, %0\n"
		: "=m" (_self->links),
		  "=r" (toAdd)
	);
	if(toAdd == 1)
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
	AutoreleasePool_Add(ThreadManager_AutoreleasePool(_threadManager), _self);
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

Object Object_DynamicallyInvoke(Object _self, Object _methodName, ...)
{
	asm(
		"pushq %%rdi\n"
		"movq %0, %%rdi\n"
		"call ListMap_ObjectAt\n"
		"movq %%rax, %%rdi\n"
		"popq %%rsi\n"
		"jmp Method_Invoke\n"
		: : "m" (_self->classInvocationMap)
	);
	// Unreachable code
	return _nil;
}

void Object_InitializeClass()
{
	Object _className = StringFactory_FromUTF8(_stringFactory, "Object", 6);
	
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Retain), StringFactory_FromUTF8(_stringFactory, "Retain", 6), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Release), StringFactory_FromUTF8(_stringFactory, "Release", 7), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Autorelease), StringFactory_FromUTF8(_stringFactory, "Autorelease", 11), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_DynamicallyInvoke), StringFactory_FromUTF8(_stringFactory, "DynamicallyInvoke", 17), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Is), StringFactory_FromUTF8(_stringFactory, "Is", 2), _className);	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Retain), StringFactory_FromUTF8(_stringFactory, "Retain", 6), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Hash), StringFactory_FromUTF8(_stringFactory, "Hash", 4), _className);
}