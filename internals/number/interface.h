#pragma once

#include "internals/actions.h"

static inline SvvInternalAction(int, IsInRange, int, int LeftBound, int RightBound)
{
	return ((Receiver >= LeftBound) && (Receiver <= RightBound));
};