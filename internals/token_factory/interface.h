#pragma once

#include "internals/basics.h"
#include "internals/token/interface.h"
#include "internals/string_map/interface.h"
#include "internals/pair_map/interface.h"
#include "internals/map/interface.h"

typedef struct SvvInternalTokenFactory {
	SvvInternalMap			reverse_keyword_map;
	SvvInternalPairMap		brackets_map;
	SvvInternalStringMap		keywords_map;
	int				default_type;
} *SvvInternalTokenFactory;

SvvInternalCreator(SvvInternalTokenFactory);
SvvInternalAction(SvvInternalTokenFactory, Destroy, void);
SvvInternalAction(SvvInternalTokenFactory, SetKeywordType, void, SvvInternalString Keyword, int Type);
SvvInternalAction(SvvInternalTokenFactory, SetBracketsType, void, SvvInternalChar Left, SvvInternalChar Right, int Type);
SvvInternalAction(SvvInternalTokenFactory, SetDefaultType, void, int Type);
SvvInternalAction(SvvInternalTokenFactory, GetTokenFromString, SvvInternalToken, SvvInternalString String);
SvvInternalAction(SvvInternalTokenFactory, GetTokenFromASCIIString, SvvInternalToken, char* String);
SvvInternalAction(SvvInternalTokenFactory, GetTokenFromKeywordType, SvvInternalToken, int Type);

