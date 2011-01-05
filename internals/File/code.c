#include "internals/basics.h"
#include "internals/File/interface.h"
#include "internals/Number/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Char/interface.h"
#include "internals/StringFactory/interface.h"
#include "internals/NumberFactory/interface.h"
#include "internals/Encoding/interface.h"

Object File_Create()
{
	File entity = Allocator_New(_allocator, sizeof(struct File));
	entity->_descriptor = 0;
	Object toReturn = Object_Create();
	toReturn->entity = entity;
	Object_SetComparator(toReturn, &File_Compare);
	Object_SetDestructor(toReturn, &File_Destroy);
	Object_SetCloner(toReturn, &File_Clone);
	toReturn->gid = 11972246422000398336ull;
	return toReturn;
}

Object File_OpenForReading(Object _self, Object _filename)
{
	File entity = _self->entity;
	char buffer[1024];
	StringFactory_GetUTF8String(_stringFactory, _filename, buffer, 1024);
	entity->_descriptor = OSfileOpen(buffer, 0);
	return _self;
}

Object File_OpenForAppending(Object _self, Object _filename)
{
	File entity = _self->entity;
	char buffer[1024];
	StringFactory_GetUTF8String(_stringFactory, _filename, buffer, 1024);
	entity->_descriptor = OSfileOpen(buffer, 2);
	return _self;
}

Object File_Close(Object _self)
{
	File entity = _self->entity;
	if(entity->_descriptor != 0)
	{
		OSfileClose(entity->_descriptor);
		entity->_descriptor = 0;
	}
	return _self;
}

Object File_TruncateToSize(Object _self, Object _size)
{
	File entity = _self->entity;
	OSfileTruncate(entity->_descriptor, Number_GetLong(_size));
	return _self;
}

Object File_SeekToPosition(Object _self, Object _position)
{
	File entity = _self->entity;
	OSfileSeek(entity->_descriptor, 0, Number_GetLong(_position));
	return _self;
}

Object File_Advance(Object _self, Object _offset)
{
	File entity = _self->entity;
	OSfileSeek(entity->_descriptor, 1, Number_GetLong(_offset));
	return _self;
}

Object File_SeekFromEndToPosition(Object _self, Object _position)
{
	File entity = _self->entity;
	OSfileSeek(entity->_descriptor, 2, Number_GetLong(_position));
	return _self;
}

Object File_GetPosition(Object _self)
{
	File entity = _self->entity;
	return NumberFactory_FromLong(_numberFactory, OSfileSeek(entity->_descriptor, 1, 0));
}

Object File_ReadByte(Object _self)
{
	File entity = _self->entity;
	char buffer;
	OSfileRead(entity->_descriptor, &buffer, 1);
	return NumberFactory_FromLong(_numberFactory, buffer);
}

Object File_WriteByte(Object _self, Object _byte)
{
	File entity = _self->entity;
	char buffer = Number_GetLong(_byte);
	OSfileWrite(entity->_descriptor, &buffer, 1);
	return _self;
}

Object File_ReadChar(Object _self)
{
	File entity = _self->entity;
	char buffer[4];
	int read = OSfileRead(entity->_descriptor, buffer, 4);
	if(read <= 0)
		return _nil;
	int charSize = UTF8GetLengthOfChar(buffer);
	if(charSize > read)
	{
		OSfileSeek(entity->_descriptor, SEEK_CUR, read);
		return _nil;
	} else {
		Object _char = Char_Create();
		Char_SetCode(_char, NumberFactory_FromLong(_numberFactory, UTF8GetCode(buffer, charSize)));
		OSfileSeek(entity->_descriptor, SEEK_CUR, read - charSize);
		return Object_Autorelease(_char);
	}
}

static inline Object File_InternalReadString(Object _self, long maxLength, long stopSymbolsLength, long* stopSymbols)
{
	Object _toReturn = List_Create();
	Object_Autorelease(_toReturn);
	while(maxLength--) {
		Object _char = File_ReadChar(_self);
		if(_char == _nil)
		{
			if(List_Size(_toReturn) == 0)
			{
				return _nil;
			} else {
				return _toReturn;
			}
		} else {
			int i;
			long code = Number_GetLong(Char_GetCode(_char));
			for(i = 0; i < stopSymbolsLength; i++)
			{
				if(code == stopSymbols[i])
					return _toReturn;
			}
			List_PushBack(_toReturn, _char);
		}
	}
	return _toReturn;
}

Object File_ReadString(Object _self)
{
	static long stopSymbols[1] = {0};
	return File_InternalReadString(_self, -1, 1, stopSymbols);
}

Object File_ReadLnString(Object _self)
{
	static long stopSymbols[3] = {0, '\n', '\r'};
	return File_InternalReadString(_self, -1, 1, stopSymbols);
}

Object File_ReadStringOfLength(Object _self, Object _length)
{
	static long stopSymbols[1] = {0};
	return File_InternalReadString(_self, Number_GetLong(_length), 1, stopSymbols);
}

Object File_ReadNumber(Object _self)
{
	static long stopSymbols[4] = {0, ' ', '\n', '\r'};
	Object _string = File_InternalReadString(_self, -1, 4, stopSymbols);
	return NumberFactory_FromString(_numberFactory, _string);
}

Object File_ReadList(Object _self);
Object File_ReadListMap(Object _self);

Object File_Compare(Object _self, Object _file)
{
	File entity1 = _self->entity;
	File entity2 = _file->entity;
	if(entity1->_descriptor > entity2->_descriptor)
		return _greater;
	if(entity1->_descriptor < entity2->_descriptor)
		return _less;
	return _equal;
}

Object File_Clone(Object _self)
{
	Object _toReturn = File_Create();
	File entity2 = _toReturn->entity;
	File entity = _self->entity;
	entity2->_descriptor = entity->_descriptor;
	return _toReturn;
}

Object File_Destroy(Object _self)
{
	File_Close(_self);
	return Object_Destroy(_self);
}

Object File_WriteNakedString(Object _self, Object _list)
{
	File entity = _self->entity;
	char buffer[1024];
	OSfileWrite(entity->_descriptor, buffer, StringFactory_GetUTF8String(_stringFactory, _list, buffer, 1024));
	return _self;
}

Object File_WriteLnString(Object _self, Object _list)
{
	File_WriteNakedString(_self, _list);
	File_WriteByte(_self, NumberFactory_FromLong(_numberFactory, '\n'));
	return _self;
}

Object File_WriteString(Object _self, Object _list)
{
	File_WriteNakedString(_self, _list);
	File_WriteByte(_self, NumberFactory_FromLong(_numberFactory, 0));
	return _self;
}

Object File_WriteNakedNumber(Object _self, Object _number)
{
	File_WriteNakedString(_self, StringFactory_FromNumber(_stringFactory, _number));
	return _self;
}

Object File_WriteNumber(Object _self, Object _number)
{
	File_WriteNakedNumber(_self, _number);
	File_WriteByte(_self, NumberFactory_FromLong(_numberFactory, 0));
	return _self;
}

Object File_WriteLnNumber(Object _self, Object _number)
{
	File_WriteNakedNumber(_self, _number);
	File_WriteByte(_self, NumberFactory_FromLong(_numberFactory, '\n'));
	return _self;
}

Object File_WriteList(Object _self, Object _list);
Object File_WriteListMap(Object _self, Object _listMap);
