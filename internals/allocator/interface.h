#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

typedef SvvInternalObject SvvInternalAllocator;

SvvInternalAction(SvvInternalAllocator, New, SvvInternalObject, int Size);
SvvInternalAction(SvvInternalAllocator, Resize, SvvInternalObject, SvvInternalObject Object, int Size);
SvvInternalAction(SvvInternalAllocator, Delete, void, SvvInternalObject Object);
