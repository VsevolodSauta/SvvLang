#pragma once

#include "internals/Object/interface.h"

Object StringFactory_Create();

Object StringFactory_FromNumber(Object receiver, Object number);
Object StringFactory_FromUTF8(Object receiver, char* string, int length);
Object StringFactory_FromCUTF8(Object receiver, char* string);
int StringFactory_GetUTF8String(Object receiver, Object string, char* buffer, int bufferLength);

void StringFactory_InitializeClass();

extern Object _stringFactory;