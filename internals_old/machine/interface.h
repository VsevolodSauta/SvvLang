#pragma once

#include "internals/basics.h"
#include "internals/list/interface.h"
#include "internals/lexer/interface.h"
#include "externals/machine/interface.h"
#include "externals/object/interface.h"

typedef struct SvvInternalMachine {
	SvvExternalObject		base;
} *SvvInternalMachine;

SvvInternalCreator(SvvInternalMachine);
SvvInternalAction(SvvInternalMachine, Execute, void, SvvInternalString Buffer);
SvvInternalAction(SvvInternalMachine, Destroy, void);
