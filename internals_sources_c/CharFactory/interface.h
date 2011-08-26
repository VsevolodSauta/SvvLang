#pragma once

#include "internals/Object/interface.h"

Object CharFactory_Create();

Object CharFactory_FromLong(Object _self, long arg);
void CharFactory_InitializeClass();

extern Object _charFactory;