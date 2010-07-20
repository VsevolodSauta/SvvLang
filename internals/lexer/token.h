#pragma once

#include "internals/string/interface.h"
#include "internals/map/interface.h"
#include "internals/string_map/interface.h"

#define LEXER_TOKEN_TYPE_END_OF_SENTENCE	1
#define LEXER_TOKEN_TYPE_END_OF_STREAM		2
#define LEXER_TOKEN_TYPE_KEYWORD_METHOD		3
#define LEXER_TOKEN_TYPE_KEYWORD_MESSAGE	4
#define LEXER_TOKEN_TYPE_KEYWORD_PROPERTY	5
#define LEXER_TOKEN_TYPE_METHOD_INVOCATION	6
#define LEXER_TOKEN_TYPE_FIELD_LINK		7
#define LEXER_TOKEN_TYPE_FIELD_NAME		8

typedef struct SvvInternalLexerToken {
	int			type;
	SvvInternalString	string;
} *SvvInternalLexerToken;

inline static SvvInternalCreator(SvvInternalLexerToken)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalLexerToken)));
};

SvvInternalRoutine(SvvInternalLexerToken, Clone, SvvInternalLexerToken)
{
	SvvInternalLexerToken to_return = SvvInternalLexerToken_Create();
	to_return->type = Receiver->type;
	to_return->string = SvvInternalString_Clone(Receiver->string);
	return to_return;
};

SvvInternalRoutine(SvvInternalLexerToken, Destroy, void)
{
	SvvInternalString_Destroy(Receiver->string);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};


