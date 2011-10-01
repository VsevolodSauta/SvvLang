#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"
#include "internals/Method/interface.h"
#include "internals/SuperClass/interface.h"

Object MethodFactory_Create()
{
	return Undestroyable_Create();
}

Object MethodFactory_FromPointer(Object _self, void* arg)
{
	Object toReturn = Method_Create();
	toReturn->entity = arg;
	return Object_Autorelease(toReturn);
}

#if 0
void MethodFactory_InitializeClass()
{
	INITIALIZE_CLASS(MethodFactory_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "MethodFactory", 13);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Undestroyable", 13);
	SuperClass_RegisterClassWithParentClass(_superClass, _className, _parentClassName);
}
#endif

Object _methodFactory;
