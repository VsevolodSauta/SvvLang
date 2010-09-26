#pragma once

#include "internals/basics.h"
#include "internals/string_map/interface.h"
#include "internals/string_set/interface.h"
#include "internals/list/interface.h"
#include "internals/string/interface.h"

typedef (*SvvInternalObject)(SvvInternalObject) SvvInternalObjectCloneRoutine;

typedef struct SvvExternalObject {
	struct SvvExternalObject*	parent;
	int				links;

	int				entity_type;
	SvvInternalObject		entity;
	SvvInternalObjectCloneRoutine	entity_clone_routine;

	SvvInternalStringSet		properties;
	SvvInternalStringMap		fields;
	SvvInternalStringMap		methods;
	SvvInternalStringMap		message_handlers;
	
	INTERLOCK_DECLARATION;
} *SvvExternalObject;

SvvInternalCreator(SvvExternalObject);
SvvInternalAction(SvvExternalObject, Clone, SvvExternalObject);
SvvInternalAction(SvvExternalObject, Derive, SvvExternalObject);

SvvInternalAction(SvvExternalObject, Destroy, void);
SvvInternalAction(SvvExternalObject, Link, void);
SvvInternalAction(SvvExternalObject, UnLink, void);
SvvInternalAction(SvvExternalObject, SetParent, void, SvvExternalObject Parent);

SvvInternalAction(SvvExternalObject, PropertySet, void, SvvInternalString Property);
SvvInternalAction(SvvExternalObject, PropertyUnSet, void, SvvInternalString Property);
SvvInternalAction(SvvExternalObject, PropertyTest, int, SvvInternalString Property);

SvvInternalAction(SvvExternalObject, SendMessage, void, SvvInternalMessage Message);



