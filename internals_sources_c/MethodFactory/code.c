#include "internals/basics.h"
#include "internals/Method/interface.h"
#include "internals/Undestroyable/interface.h"
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

void MethodFactory_InitializeClass()
{
}

Object _methodFactory;
