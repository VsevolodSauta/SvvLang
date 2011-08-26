#pragma once

#include "internals/Object/interface.h"

Object MethodFactory_Create();

Object MethodFactory_FromPointer(Object _self, void* arg);

void MethodFactory_InitializeClass();

extern Object _methodFactory;