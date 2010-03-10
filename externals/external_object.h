#pragma once

#include "internal_actions.h"
#include "internal_map.h"
#include "internal_object.h"

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