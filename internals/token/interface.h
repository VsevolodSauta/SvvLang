#pragma once

#include "internals/string/interface.h"
#include "internals/map/interface.h"
#include "internals/string_map/interface.h"

#define TOKEN_TYPE_END_OF_SENTENCE	1
#define TOKEN_TYPE_KEYWORD_METHOD	3
#define TOKEN_TYPE_KEYWORD_MESSAGE	4
#define TOKEN_TYPE_KEYWORD_PROPERTY	5
#define TOKEN_TYPE_METHOD_INVOCATION	6
#define TOKEN_TYPE_FIELD_LINK		7
#define TOKEN_TYPE_IDENTIFIER		8

typedef struct SvvInternalToken {
	int			type;
	SvvInternalString	string;
} *SvvInternalToken;

inline static SvvInternalCreator(SvvInternalToken)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalToken)));
};

SvvInternalRoutine(SvvInternalToken, Clone, SvvInternalToken)
{
	SvvInternalToken to_return = SvvInternalToken_Create();
	to_return->type = Receiver->type;
	to_return->string = SvvInternalString_Clone(Receiver->string);
	return to_return;
};

SvvInternalRoutine(SvvInternalToken, Destroy, void)
{
	SvvInternalString_Destroy(Receiver->string);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};


