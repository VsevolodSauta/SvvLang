#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "internal_list.h"

typedef SvvInternalList SvvInternalStack;

SvvInternalCreator(SvvInternalStack);
SvvInternalAction(SvvInternalStack, Destroy, void);
SvvInternalAction(SvvInternalStack, Push, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalStack, Pop, SvvInternalObject);
SvvInternalAction(SvvInternalStack, Peek, SvvInternalObject);
SvvInternalAction(SvvInternalStack, Clean, void);
SvvInternalAction(SvvInternalStack, Clone, SvvInternalStack);

