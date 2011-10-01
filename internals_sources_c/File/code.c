#include "internals/basics.h"
#include "internals/File/interface.h"
#include "internals/Undestroyable/interface.h"
#include "internals/Number/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Char/interface.h"
#include "internals/StringFactory/interface.h"
#include "internals/NumberFactory/interface.h"
#include "internals/File/encoding.h"
#include "internals/Logic/interface.h"
#include "internals/Comparison/interface.h"
#include "internals/SuperClass/interface.h"

#define BUFFER_LENGTH 4096
#define FileGID 11972246422000398336ull

Object File_Create()
{
	File entity = Allocator_New(_allocator, sizeof(struct File));
	entity->_descriptor = 0;
	Object toReturn = Object_Create();
	toReturn->entity = entity;
	toReturn->destroy = &File_Destroy;
	toReturn->gid = FileGID;
	return toReturn;
}

Object File_OpenForReading(Object _self, Object _filename)
{
	File entity = _self->entity;
	char buffer[BUFFER_LENGTH];
	StringFactory_GetUTF8String(_stringFactory, _filename, buffer, BUFFER_LENGTH);
	entity->_descriptor = OSfileOpen(buffer, 0);
	return _self;
}

Object File_OpenForAppending(Object _self, Object _filename)
{
	File entity = _self->entity;
	char buffer[BUFFER_LENGTH];
	StringFactory_GetUTF8String(_stringFactory, _filename, buffer, BUFFER_LENGTH);
	entity->_descriptor = OSfileOpen(buffer, 66, 0777);
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

Object File_ErrorWhileOpenning(Object _self)
{
	File entity = _self->entity;
	return LogicFactory_FromLong(_logicFactory, entity->_descriptor < 0);
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
	OSfileSeek(entity->_descriptor, Number_GetLong(_position), 0);
	return _self;
}

Object File_Advance(Object _self, Object _offset)
{
	File entity = _self->entity;
	OSfileSeek(entity->_descriptor, Number_GetLong(_offset), 1);
	return _self;
}

Object File_SeekFromEndToPosition(Object _self, Object _position)
{
	File entity = _self->entity;
	OSfileSeek(entity->_descriptor, Number_GetLong(_position), 2);
	return _self;
}

Object File_GetPosition(Object _self)
{
	File entity = _self->entity;
	return NumberFactory_FromLong(_numberFactory, OSfileSeek(entity->_descriptor, 0, 1));
}

Object File_ReadByte(Object _self)
{
	File entity = _self->entity;
	char buffer;
	OSfileRead(entity->_descriptor, &buffer, 1);
	return NumberFactory_FromLong(_numberFactory, buffer);
}

Object File_ReadChar(Object _self)
{
	File entity = _self->entity;
	char buffer[16];
	int read = OSfileRead(entity->_descriptor, buffer, 16);
	if(read <= 0)
		return _nil;
	int charSize = UTF8GetLengthOfChar(buffer);
	if(charSize > read)
	{
		OSfileSeek(entity->_descriptor, -read, 1);
		return _nil;
	} else {
		Object _char = Char_Create();
		Number_SetLong(Char_GetMutableCode(_char), UTF8GetCode(buffer, charSize));
		OSfileSeek(entity->_descriptor, charSize - read, 1);
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
			long code = Number_GetLong(Char_GetMutableCode(_char));
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

Object File_ReadContentsOfFile(Object _self)
{
	return File_InternalReadString(_self, -1, 0, 0);
}

Object File_CompareSameGID(Object _self, Object _file)
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

Object File_WriteByte(Object _self, Object _byte)
{
	File entity = _self->entity;
	char buffer = Number_GetLong(_byte);
	OSfileWrite(entity->_descriptor, &buffer, 1);
	return _self;
}

Object File_WriteChar(Object _self, Object _char)
{
	File entity = _self->entity;
	char buffer[16];
	long code;
	long length;
	code = Number_GetLong(Char_GetCode(_char));
	length = UTF8GetLengthOfCode(code);
	UTF8PutChar(buffer, code, length);
	OSfileWrite(entity->_descriptor, buffer, length);
	return _self;
}

Object File_WriteNakedString(Object _self, Object _list)
{
	File entity = _self->entity;
	char buffer[16];
	long code;
	long length;
	Object iterator = List_First(_list);
	while(ListIterator_ThisEnd(iterator) != _true)
	{
		code = Number_GetLong(Char_GetCode(ListIterator_ThisData(iterator)));
		length = UTF8GetLengthOfCode(code);
		UTF8PutChar(buffer, code, length);
		OSfileWrite(entity->_descriptor, buffer, length);
		ListIterator_Next(iterator);
	}
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

void File_InitializeClass()
{
	INITIALIZE_CLASS(File_InitializeClass);
	Object _className = StringFactory_FromUTF8(_stringFactory, "File", 4);
	Object _parentClassName = StringFactory_FromUTF8(_stringFactory, "Object", 6);
	Object _gid = NumberFactory_FromLong(_numberFactory, FileGID);
	SuperClass_RegisterClassWithNameWithGIDWithParentClassName(_superClass, _className, _gid, _parentClassName);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_Clone), StringFactory_FromUTF8(_stringFactory, "Clone", 5), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_Clone), StringFactory_FromUTF8(_stringFactory, "DeepClone", 9), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_Destroy), StringFactory_FromUTF8(_stringFactory, "Destroy", 7), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_CompareSameGID), StringFactory_FromUTF8(_stringFactory, "CompareSameGID", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_OpenForAppending), StringFactory_FromUTF8(_stringFactory, "OpenForAppending", 16), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_OpenForReading), StringFactory_FromUTF8(_stringFactory, "OpenForReading", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_Close), StringFactory_FromUTF8(_stringFactory, "Close", 5), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_TruncateToSize), StringFactory_FromUTF8(_stringFactory, "TruncateToSize", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ErrorWhileOpenning), StringFactory_FromUTF8(_stringFactory, "ErrorWhileOpenning", 18), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_SeekToPosition), StringFactory_FromUTF8(_stringFactory, "SeekToPosition", 14), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_Advance), StringFactory_FromUTF8(_stringFactory, "Advance", 7), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_SeekFromEndToPosition), StringFactory_FromUTF8(_stringFactory, "SeekFromEndToPosition", 21), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_GetPosition), StringFactory_FromUTF8(_stringFactory, "GetPosition", 11), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadByte), StringFactory_FromUTF8(_stringFactory, "ReadByte", 8), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadChar), StringFactory_FromUTF8(_stringFactory, "ReadChar", 8), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadString), StringFactory_FromUTF8(_stringFactory, "ReadString", 10), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadLnString), StringFactory_FromUTF8(_stringFactory, "ReadLnString", 12), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadStringOfLength), StringFactory_FromUTF8(_stringFactory, "ReadStringOfLength", 18), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadNumber), StringFactory_FromUTF8(_stringFactory, "ReadNumber", 9), _className);
	//SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadList), StringFactory_FromUTF8(_stringFactory, "ReadList", 8), _className);
	//SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadListMap), StringFactory_FromUTF8(_stringFactory, "ReadListMap", 11), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_ReadContentsOfFile), StringFactory_FromUTF8(_stringFactory, "ReadContentsOfFile", 18), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteByte), StringFactory_FromUTF8(_stringFactory, "WriteByte", 9), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteChar), StringFactory_FromUTF8(_stringFactory, "WriteChar", 9), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteString), StringFactory_FromUTF8(_stringFactory, "WriteString", 11), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteLnString), StringFactory_FromUTF8(_stringFactory, "WriteLnString", 13), _className);
	SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteNumber), StringFactory_FromUTF8(_stringFactory, "WriteNumber", 10), _className);
	//SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteList), StringFactory_FromUTF8(_stringFactory, "WriteList", 9), _className);
	//SuperClass_RegisterMethodWithNameForClassWithName(_superClass, MethodFactory_FromPointer(_methodFactory, &File_WriteListMap), StringFactory_FromUTF8(_stringFactory, "WriteListMap", 12), _className);
}
