#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"
#include "internals/Logic/interface.h"
#include "internals/SuperClass/interface.h"

Object _logicFactory;

Object LogicFactory_Create()
{
	return Undestroyable_Create();
}

Object LogicFactory_FromLong(Object receiver, long arg)
{
	return arg ? _true : _false;
}

void LogicFactory_InitializeClass()
{

}