#include "internals/basics.h"

Object LogicFactory_FromLong(Object receiver, long arg)
{
	return arg ? true : false;
}