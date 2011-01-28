#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

Object _less;
Object _greater;
Object _equal;
Object _uncomparableLess;
Object _uncomparableGreater;

Object Comparation_Create()
{
	return Undestroyable_Create();
}