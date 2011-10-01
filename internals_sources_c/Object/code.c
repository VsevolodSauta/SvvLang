#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"
#include "internals/ThreadManager/interface.h"
#include "internals/AutoreleasePool/interface.h"
#include "internals/Logic/interface.h"
#include "internals/ListMap/interface.h"
#include "internals/Comparison/interface.h"
#include "internals/SuperClass/interface.h"

#define ObjectGID 2803832687958515712ull

Object Object_Create(void)
{
	Object toReturn = Allocator_New(_allocator, sizeof(struct Object));
	toReturn->links = 1;
	toReturn->gid = ObjectGID;
	toReturn->destroy = &Object_Destroy;
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
			return Object_DynamicallyInvoke(_self, StringFactory_FromUTF8(_stringFactory, "CompareSameGID", 14), object);
		}
	}
}

Object Object_CompareSameGID(Object _self, Object object)
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
	Allocator_Delete(_allocator, _self->entity);
	return Allocator_Delete(_allocator, _self);
}

Object Object_Clone(Object _self)
{
	return Object_Retain(_self);
}

Object Object_TempClone(Object _self)
{
	return _self;
}

Object Object_DeepClone(Object _self)
{
	return Object_Retain(_self);
}

Object Object_TempDeepClone(Object _self)
{
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
	Object _gid = NumberFactory_FromLong(_numberFactory, _self->gid);
	Object _className = SuperClass_ClassNameForGID(_superClass, _gid);
	Object _implementation = SuperClass_MethodWithNameInClassWithName(_superClass, _methodName, _className);
	
	while(_implementation == _nil) {
		_className = SuperClass_ParentClassNameForClassWithName(_superClass, _className);
		if(_className == _nil)
		{
			ASSERT_C("Unable to find the method for dynamic invocation.", 0);
		}
		_implementation = SuperClass_MethodWithNameInClassWithName(_superClass, _methodName, _className);
	}
	
	asm(
		"movq %%rdi, %%rsi\n"
		"movq %0, %%rdi\n"
		"jmp Method_Invoke\n"
		: 
		: 
		"m" (_implementation)
	);
	
	// Unreachable code
	return _nil;
}

void Object_InitializeClass()
{
	INITIALIZE_CLASS(Object_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "Object", 6);
	Object _gid = NumberFactory_FromLong(_numberFactory, ObjectGID);
	SuperClass_RegisterClassWithNameWithGIDWithParentClassName(_superClass, _className, _gid, _nil);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Retain), StringFactory_FromUTF8(_stringFactory, "Retain", 6), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Release), StringFactory_FromUTF8(_stringFactory, "Release", 7), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Autorelease), StringFactory_FromUTF8(_stringFactory, "Autorelease", 11), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Compare), StringFactory_FromUTF8(_stringFactory, "Compare", 7), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_CompareSameGID), StringFactory_FromUTF8(_stringFactory, "CompareSameGID", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_DynamicallyInvoke), StringFactory_FromUTF8(_stringFactory, "DynamicallyInvoke", 17), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Is), StringFactory_FromUTF8(_stringFactory, "Is", 2), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Object_Hash), StringFactory_FromUTF8(_stringFactory, "Hash", 4), _className);
}
