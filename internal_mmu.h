#pragma once

#include "internal_actions.h"
#include "internal_object.h"

typedef SvvInternalObject SvvInternalMMU;

SvvInternalAction(SvvInternalMMU, Copy, void, SvvInternalObject DestObject, SvvInternalObject SrcObject, int Size);
SvvInternalAction(SvvInternalMMU, Compare, int, SvvInternalObject Object1, SvvInternalObject Object2, int Size);
