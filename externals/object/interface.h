#pragma once

#include "internals/basics.h"
#include "internals/string_map/interface.h"
#include "internals/string_set/interface.h"
#include "internals/list/interface.h"
#include "internals/string/interface.h"

typedef struct SvvExternalObject {
	struct SvvExternalObject*	parent;
	int				links;
	int				entity_type;
	SvvInternalObject		entity;
	SvvInternalStringSet		properties;
	SvvInternalStringMap		fields;
	SvvInternalSet			methods;
	SvvInternalStringMap		message_handlers;
	SvvInternalList			code;
	SvvInternalString		token;
	int				token_type;
} *SvvExternalObject;

SvvInternalCreator(SvvExternalObject);
SvvInternalAction(SvvExternalObject, Destroy, void);
SvvInternalAction(SvvExternalObject, Link, void);
SvvInternalAction(SvvExternalObject, UnLink, void);
SvvInternalAction(SvvExternalObject, Clone, SvvExternalObject);
SvvInternalAction(SvvExternalObject, Derive, SvvExternalObject);
SvvInternalAction(SvvExternalObject, SetParent, void, SvvExternalObject Parent);

SvvInternalAction(SvvExternalObject, PropertySet, void, SvvInternalString Property);
SvvInternalAction(SvvExternalObject, PropertyUnSet, void, SvvInternalString Property);
SvvInternalAction(SvvExternalObject, PropertyTest, int, SvvInternalString Property);

SvvInternalAction(SvvExternalObject, CodeSet, void, SvvInternalList Code);

SvvInternalAction(SvvExternalObject, Run, void);


