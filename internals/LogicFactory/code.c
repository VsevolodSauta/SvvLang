#include "internals/basics.h"

Object _logicFactory;

Object LogicFactory_Create()
{
	return Undestroyable_Create();
}

Object LogicFactory_FromLong(Object receiver, long arg)
{
	return arg ? _true : _false;
}