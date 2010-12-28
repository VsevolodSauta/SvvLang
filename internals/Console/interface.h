#pragma once

#include "internals/Object/interface.h"

Object Console_Create();
Object Console_Compare(Object receiver, Object console);
Object Console_Clone(Object receiver);
Object Console_Destroy(Object receiver);

Object Console_PrintNumber(Object receiver, Object number);
Object Console_PrintString(Object receiver, Object list);
Object Console_PrintLnNumber(Object receiver, Object number);
Object Console_PrintLnString(Object receiver, Object list);
Object Console_ReadString(Object receiver);