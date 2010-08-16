#pragma once

#include "internals/basics.h"
#include "internals/list/interface.h"

typedef struct SvvInternalMessage {
	SvvInternalList		tokens;
} *SvvInternalMessage;

SvvInternalCreator(SvvInternalMessage);
SvvInternalAction(SvvInternalMessage, Destroy, void);
SvvInternalAction(SvvInternalMessage, TokenAppend, void, SvvInternalToken Token);
SvvInternalAction(SvvInternalMessage, ListAppend, void, SvvInternalList List);

