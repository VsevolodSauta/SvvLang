#include "internals/basics.h"
#include "internals/Method/interface.h"

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

Object _methodFactory;
