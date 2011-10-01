#include "internals/basics.h"
#include "internals/Method/interface.h"
#include "internals/Undestroyable/interface.h"
#include "internals/Comparison/interface.h"
#include "internals/SuperClass/interface.h"

#define MethodGID 14849865630305968128ull

Object Method_Create()
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_GetUndeletable(_allocator);
	toReturn->gid = MethodGID;
	toReturn->destroy = &Method_Destroy;
	return toReturn;
}

Object Method_CompareSameGID(Object _self, Object _method)
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

void Method_InitializeClass()
{
	INITIALIZE_CLASS(Method_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "Method", 5);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Object", 6);
	Object _gid = NumberFactory_FromLong(_numberFactory, MethodGID);
	SuperClass_RegisterClassWithNameWithGIDWithParentClassName(_superClass, _className, _gid, _parentClassName);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_Clone), StringFactory_FromUTF8(_stringFactory, "DeepClone", 9), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_Clone), StringFactory_FromUTF8(_stringFactory, "Clone", 5), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_Destroy), StringFactory_FromUTF8(_stringFactory, "Destroy", 7), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_CompareSameGID), StringFactory_FromUTF8(_stringFactory, "CompareSameGID", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_Invoke), StringFactory_FromUTF8(_stringFactory, "Invoke", 6), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &Method_Invoke), StringFactory_FromUTF8(_stringFactory, "Call", 4), _className);
}
