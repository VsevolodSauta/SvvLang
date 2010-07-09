#pragma once

#include "internals/globals.h"
#include "internals/string_map/interface.h"

typedef struct {
	int			used;
	int			ptr_entity;
	SvvInternalObject	entity;
	SvvInternalStringMap	internals;
	SvvInternalStringMap	methods;
	SvvInternalStringMap	messages;
} *SvvExternalObject;

SvvInternalAction(SvvExternalObject, Create, SvvExternalObject);
SvvInternalAction(SvvExternalObject, Destroy, void);
SvvInternalAction(SvvExternalObject, Link, void);
SvvInternalAction(SvvExternalObject, Unlink, void);