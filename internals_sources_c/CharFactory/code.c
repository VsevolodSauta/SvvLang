#include "internals/basics.h"
#include "internals/Number/interface.h"
#include "internals/Undestroyable/interface.h"
#include "internals/Char/interface.h"
#include "internals/SuperClass/interface.h"

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
}

#if 0
void CharFactory_InitializeClass()
{
	INITIALIZE_CLASS(CharFactory_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "CharFactory", 10);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Undestroyable", 13);
	SuperClass_RegisterClassWithParentClass(_superClass, _className, _parentClassName);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &CharFactory_FromLong), StringFactory_FromUTF8(_stringFactory, "FromLong", 8), _className);
}
#endif

Object _charFactory;