#pragma once

#include "internal_actions.h"
#include "internal_object.h"

typedef SvvInternalObject SvvInternalAllocator;

SvvInternalAction(SvvInternalAllocator, New, SvvInternalObject, int Size);
SvvInternalAction(SvvInternalAllocator, Resize, SvvInternalObject, SvvInternalObject Object, int Size);
SvvInternalAction(SvvInternalAllocator, Delete, void, SvvInternalObject Object);
