#pragma once

#include "internal_action.h"
#include "internal_list.h"

typedef struct {
	SvvInternalList		objects;
} *SvvInternalMachine;

SvvInternalAction(SvvInternalMachine, Create, void);
SvvInternalAction(SvvInternalMachine, Run, char* Buffer);
SvvInternalAction(SvvInternalMachine, Destroy);