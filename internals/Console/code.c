#include "internals/basics.h"
#include "internals/Number/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Char/interface.h"
#include "internals/StringFactory/interface.h"

Object Console_Create()
{
	return Undestroyable_Create();
}

Object Console_Compare(Object receiver, Object console)
{
	return _equal;
}

Object Console_Clone(Object receiver)
{
	return receiver;
}

Object Console_Destroy(Object receiver)
{
	return receiver;
}

Object Console_PrintLnNumber(Object receiver, Object number)
{
	Console_PrintLnString(receiver, StringFactory_FromNumber(_stringFactory, number));
	return receiver;
}

Object Console_PrintString(Object receiver, Object list)
{
	char buffer[1024];
	write(0, buffer, StringFactory_GetUTF8String(_stringFactory, list, buffer, 1024));
	return receiver;
}

Object Console_PrintLnString(Object receiver, Object list)
{
	char buffer[1024];
	write(0, buffer, StringFactory_GetUTF8String(_stringFactory, list, buffer, 1024));
	write(0, "\n", 1);
	return receiver;
}

Object Console_ReadString(Object receiver)
{
	char buffer[1024];
	Object toReturn = StringFactory_FromUTF8(_stringFactory, buffer, read(0, buffer, 1024));
	return toReturn;
}

Object _console;
