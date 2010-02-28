#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "internal_list.h"

typedef SvvInternalList SvvInternalQueue;

SvvInternalCreator(SvvInternalQueue);
SvvInternalAction(SvvInternalQueue, Destroy, void);
SvvInternalAction(SvvInternalQueue, Push, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalQueue, Pop, SvvInternalObject);
SvvInternalAction(SvvInternalQueue, Peek, SvvInternalObject);
SvvInternalAction(SvvInternalQueue, Clean, void);
