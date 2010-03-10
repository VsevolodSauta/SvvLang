#pragma once

#include "internals/basics.h"
#include "internals/list/interface.h"

typedef SvvInternalList SvvInternalQueue;

SvvInternalCreator(SvvInternalQueue);
SvvInternalAction(SvvInternalQueue, Destroy, void);
SvvInternalAction(SvvInternalQueue, Push, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalQueue, Pop, SvvInternalObject);
SvvInternalAction(SvvInternalQueue, Peek, SvvInternalObject);
SvvInternalAction(SvvInternalQueue, Clean, void);
