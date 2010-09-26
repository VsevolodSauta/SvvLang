#pragma once

#include "internals/basics.h"
#include "internals/map/interface.h"

typedef SvvInternalMap SvvInternalPairMap;

SvvInternalCreator(SvvInternalPairMap);
SvvInternalAction(SvvInternalPairMap, Destroy, void);
SvvInternalAction(SvvInternalPairMap, Add, void, SvvInternalObject Key1, SvvInternalObject Key2, SvvInternalObject Value);
SvvInternalAction(SvvInternalPairMap, RemoveKey, void, SvvInternalObject Key1, SvvInternalObject Key2);
SvvInternalAction(SvvInternalPairMap, Clean, void);
SvvInternalAction(SvvInternalPairMap, ExistsKey, int, SvvInternalObject Key1, SvvInternalObject Key2);
SvvInternalAction(SvvInternalPairMap, GetValue, SvvInternalObject, SvvInternalObject Key1, SvvInternalObject Key2);
