#pragma once

#include "internals/Object/interface.h"

typedef struct File {
	int	_descriptor;
} *File;

Object File_Create();
Object File_OpenForReading(Object _self, Object _filename);
Object File_OpenForAppending(Object _self, Object _filename);
Object File_Close(Object _self);
Object File_TruncateToSize(Object _self, Object _size);

Object File_SeekToPosition(Object _self, Object _position);
Object File_Advance(Object _self, Object _offset);
Object File_SeekFromEndToPosition(Object _self, Object _position);
Object File_GetPosition(Object _self);

Object File_ReadByte(Object _self);
Object File_WriteByte(Object _self, Object _byteCode);

Object File_ReadChar(Object _self);
Object File_ReadString(Object _self);
Object File_ReadLnString(Object _self);
Object File_ReadStringOfLength(Object _self, Object _length);
Object File_ReadNumber(Object _self);

Object File_ReadList(Object _self);
Object File_ReadListMap(Object _self);

Object File_Compare(Object _self, Object _file);
Object File_Clone(Object _self);
Object File_Destroy(Object _self);

Object File_WriteNakedNumber(Object _self, Object _number);
Object File_WriteNakedString(Object _self, Object _list);
Object File_WriteNumber(Object _self, Object _number);
Object File_WriteString(Object _self, Object _list);
Object File_WriteLnNumber(Object _self, Object _number);
Object File_WriteLnString(Object _self, Object _list);
Object File_WriteList(Object _self, Object _list);
Object File_WriteListMap(Object _self, Object _listMap);
