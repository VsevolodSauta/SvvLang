#pragma once

#include "internal_config.h"
#include "internal_globals.h"
#include "internal_actions.h"
#include "internal_object.h"
#include "internal_list.h"

typedef SvvInternalList SvvInternalStringSet;

typedef struct {
	SvvInternalStringSet son;
	SvvInternalChar data;
} *SvvInternalStringSetEntry;

SvvInternalCreator(SvvInternalStringSet);
SvvInternalAction(SvvInternalStringSet, Destroy, void);
SvvInternalAction(SvvInternalStringSet, Add, void, SvvInternalString);
SvvInternalAction(SvvInternalStringSet, Remove, void, SvvInternalString);
SvvInternalAction(SvvInternalStringSet, Exists, int, SvvInternalString);
SvvInternalAction(SvvInternalStringSet, GetList, SvvInternalList);
