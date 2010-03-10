#pragma once

#include "internals/basics.h"
#include "internals/list/interface.h"

typedef SvvInternalList SvvInternalStack;

SvvInternalCreator(SvvInternalStack);
SvvInternalAction(SvvInternalStack, Destroy, void);
SvvInternalAction(SvvInternalStack, Push, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalStack, Pop, SvvInternalObject);
SvvInternalAction(SvvInternalStack, Peek, SvvInternalObject);
SvvInternalAction(SvvInternalStack, Clean, void);
SvvInternalAction(SvvInternalStack, Clone, SvvInternalStack);
SvvInternalAction(SvvInternalStack, IsEmpty, int);
