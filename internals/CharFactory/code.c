#include "internals/Number/interface.h"
#include "internals/Char/interface.h"
#include "internals/basics.h"

Object CharFactory_Create()
{
	return Undestroyable_Create();
}

Object CharFactory_FromLong(Object _self, long _arg)
{
	DMSG("Char factory: Creating char.\n");
	Object _toReturn = Char_Create();
	Number_SetLong(Char_GetMutableCode(_toReturn), _arg);
	Object_Autorelease(_toReturn);
	return _toReturn;
};

Object _charFactory;