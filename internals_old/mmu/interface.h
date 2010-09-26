#pragma once

#include "internals/object/interface.h"

typedef SvvInternalObject SvvInternalMMU;

SvvInternalAction(SvvInternalMMU, Copy, void, SvvInternalObject DestObject, SvvInternalObject SrcObject, int Size);
SvvInternalAction(SvvInternalMMU, Compare, int, SvvInternalObject Object1, SvvInternalObject Object2, int Size);
