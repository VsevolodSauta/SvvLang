#pragma once

#include "internals/Object/interface.h"

Object Method_Create();
Object Method_Invoke(Object _self, Object _object, ...);
Object Method_Compare(Object, Object);
Object Method_Destroy(Object);
Object Method_Clone(Object);