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

#if 0
void LogicFactory_InitializeClass()
{
	INITIALIZE_CLASS(LogicFactory_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "LogicFactory", 12);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Undestroyable", 13);
	SuperClass_RegisterClassWithParentClass(_superClass, _className, _parentClassName);
	
}
#endif