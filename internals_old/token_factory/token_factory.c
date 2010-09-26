#include "internals/basics.h"
#include "internals/token_factory/interface.h"
#include "internals/string_map/interface.h"
#include "internals/pair_map/interface.h"
#include "internals/token/interface.h"
#include "internals/string/interface.h"
#include "internals/string_factory/interface.h"

SvvInternalCreator(SvvInternalTokenFactory)
{
	SvvInternalTokenFactory factory =
		OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalTokenFactory)));
	factory->keywords_map = SvvInternalStringMap_Create();
	factory->brackets_map = SvvInternalPairMap_Create();
	factory->reverse_keyword_map = SvvInternalMap_Create();
	return factory;
};

SvvInternalAction(SvvInternalTokenFactory, Destroy, void)
{
	SvvInternalStringMap_Destroy(Receiver->keywords_map);
	SvvInternalPairMap_Destroy(Receiver->brackets_map);
	SvvInternalMap_Destroy(Receiver->reverse_keyword_map);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalTokenFactory, SetKeywordType, void, SvvInternalString Keyword, int Type)
{
	SvvInternalStringMap_Add(Receiver->keywords_map, Keyword, INT_AS_OBJECT(Type));
	SvvInternalMap_Add(Receiver->reverse_keyword_map, INT_AS_OBJECT(Type), LINK_AS_OBJECT(Keyword));
};

SvvInternalAction(SvvInternalTokenFactory, SetBracketsType, void, SvvInternalChar Left, SvvInternalChar Right, int Type)
{
	SvvInternalPairMap_Add(Receiver->brackets_map, CHAR_AS_OBJECT(Left), CHAR_AS_OBJECT(Right), INT_AS_OBJECT(Type));
};

SvvInternalAction(SvvInternalTokenFactory, SetDefaultType, void, int Type)
{
	Receiver->default_type = Type;
};

SvvInternalRoutine(SvvInternalTokenFactory, DetermineTokenType, void, SvvInternalToken Token)
{
	if(SvvInternalStringMap_ExistsKey(Receiver->keywords_map, Token->string))
	{
		Token->type = OBJECT_AS_INT(SvvInternalStringMap_GetValue(Receiver->keywords_map, Token->string));
		return;
	};

	SvvInternalStringIterator first_position = SvvInternalString_GetFirst(Token->string);
	SvvInternalStringIterator last_position = SvvInternalString_GetLast(Token->string);
	int first_char_code = SvvInternalChar_GetCode(SvvInternalStringIterator_CharGet(first_position));
	int last_char_code = SvvInternalChar_GetCode(SvvInternalStringIterator_CharGet(last_position));
	
	SvvInternalStringIterator_Destroy(first_position);
	SvvInternalStringIterator_Destroy(last_position);
	
	if(SvvInternalPairMap_ExistsKey(Receiver->brackets_map, 
		INT_AS_OBJECT(first_char_code), INT_AS_OBJECT(last_char_code)))
	{
		Token->type = OBJECT_AS_INT(SvvInternalPairMap_GetValue(Receiver->brackets_map, 
			INT_AS_OBJECT(first_char_code), INT_AS_OBJECT(last_char_code)));
		return;
	};

	Token->type = Receiver->default_type;
	return;
};

SvvInternalAction(SvvInternalTokenFactory, GetTokenFromString, SvvInternalToken, SvvInternalString String)
{
	SvvInternalToken token = SvvInternalToken_Create();
	token->string = String;
	SvvInternalTokenFactory_DetermineTokenType(Receiver, token);
	return token;
};

SvvInternalAction(SvvInternalTokenFactory, GetTokenFromASCIIString, SvvInternalToken, char* String)
{
	SvvInternalToken token = SvvInternalToken_Create();
	token->string = SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, String);
	SvvInternalTokenFactory_DetermineTokenType(Receiver, token);
	return token;
};

SvvInternalAction(SvvInternalTokenFactory, GetTokenFromKeywordType, SvvInternalToken, int Type)
{
	return OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver->reverse_keyword_map, INT_AS_OBJECT(Type)));
};

