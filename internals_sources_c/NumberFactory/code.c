#include "internals/basics.h"
#include "internals/NumberFactory/interface.h"
#include "internals/Undestroyable/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Char/interface.h"
#include "internals/Logic/interface.h"
#include "internals/SuperClass/interface.h"

Object NumberFactory_Create()
{
	return Undestroyable_Create();
}

Object NumberFactory_FromLong(Object _self, long _arg)
{
	DPUSHS("Number factory: Creating number.");
	Object _toReturn = Number_Create();
	Number_SetLong(_toReturn, _arg);
	Object_Autorelease(_toReturn);
	DPOPS("Number factory: Number created.");
	return _toReturn;
};

Object NumberFactory_FromString(Object _self, Object _string)
{
	Object _toReturn = Number_Create();
	Object_Autorelease(_toReturn);
	Object _iterator = List_Last(_string);
	long position = 1;
	long actual = 0;
	while(ListIterator_ThisBegin(_iterator) != _true) {
		Object _currentChar = ListIterator_ThisData(_iterator);
		int charCode = Number_GetLong(Char_GetCode(_currentChar));
		switch(charCode)
		{
			case ',':
				break;
			case '.':
				// Not supported yet
				break;
			case '-':
				if(ListIterator_PrevBegin(_iterator) == _true)
				{
					actual = -actual;
					break;
				} else {
					return _nil;
				}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				actual += position * (charCode - '0');
				position *= 10;
				break;
			default:
				return _nil;
		}
		ListIterator_Prev(_iterator);
	}
	Number_SetLong(_toReturn, actual);
	return _toReturn;
}

Object NumberFactory_FromHexString(Object _self, Object _string)
{
	Object _toReturn = Number_Create();
	Object_Autorelease(_toReturn);
	Object _iterator = List_Last(_string);
	long position = 1;
	long actual = 0;
	while(ListIterator_ThisBegin(_iterator) != _true) {
		Object _currentChar = ListIterator_ThisData(_iterator);
		int charCode = Number_GetLong(Char_GetCode(_currentChar));
		switch(charCode)
		{
			case ',':
				break;
			case '.':
				// Not supported yet
				break;
			case '-':
				if(ListIterator_PrevBegin(_iterator) == _true)
				{
					actual = -actual;
					break;
				} else {
					return _nil;
				}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				actual += position * (charCode - '0');
				position *= 16;
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				actual += position * (charCode - 'a' + 10);
				position *= 16;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				actual += position * (charCode - 'A' + 10);
				position *= 16;
				break;
			default:
				return _nil;
		}
		ListIterator_Prev(_iterator);
	}
	Number_SetLong(_toReturn, actual);
	return _toReturn;
}

#if 0
void NumberFactory_InitializeClass()
{
	Object _className = StringFactory_FromUTF8(_stringFactory, "NumberFactory", 13);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Undestroyable", 13);
	SuperClass_RegisterClassWithParentClass(_superClass, _className, _parentClassName);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &NumberFactory_FromLong), StringFactory_FromUTF8(_stringFactory, "FromLong", 8), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &NumberFactory_FromString), StringFactory_FromUTF8(_stringFactory, "FromString", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &NumberFactory_FromHexString), StringFactory_FromUTF8(_stringFactory, "FromHexString", 13), _className);
}
#endif

Object _numberFactory;
