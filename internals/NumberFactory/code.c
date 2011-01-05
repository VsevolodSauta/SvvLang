#include "internals/NumberFactory/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Char/interface.h"
#include "internals/basics.h"

Object NumberFactory_Create()
{
	return Undestroyable_Create();
}

Object NumberFactory_FromLong(Object _self, long _arg)
{
	DMSG("Number factory: Creating number.\n");
	Object _toReturn = Number_Create();
	Number_SetLong(_toReturn, _arg);
	Object_Autorelease(_toReturn);
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

Object _numberFactory;
