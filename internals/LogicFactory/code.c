#include "internals/basics.h"

Object _logicFactory;

Object LogicFactory_FromLong(Object receiver, long arg)
{
	return arg ? _true : _false;
}