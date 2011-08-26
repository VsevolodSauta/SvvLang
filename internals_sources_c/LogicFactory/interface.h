#include "internals/Object/interface.h"

Object LogicFactory_Create();

Object LogicFactory_FromLong(Object receiver, long arg);

void Logic_InitializeClass();

extern Object _logicFactory;