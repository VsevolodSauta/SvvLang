#include "internals/basics.h"
#include "internals/lexer/interface.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"
#include "internals/set/interface.h"
#include "internals/string_map/interface.h"
#include "internals/pair_map/interface.h"
#include "internals/lexer/token.h"

SvvInternalCreator(SvvInternalLexer)
{
	SvvInternalLexer lexer = 
		OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalLexer)));
	lexer->delimiters_set = SvvInternalSet_Create();
	lexer->keywords_map = SvvInternalStringMap_Create();
	lexer->brackets_map = SvvInternalPairMap_Create();
	return lexer;
};

SvvInternalAction(SvvInternalLexer, AddDelimiter, void, SvvInternalChar Char)
{
	SvvInternalSet_Add(Receiver->delimiters_set, CHAR_AS_OBJECT(Char));
};

SvvInternalAction(SvvInternalLexer, SetKeywordType, void, SvvInternalString Keyword, int Type)
{
	SvvInternalStringMap_Add(Receiver->keywords_map, Keyword, INT_AS_OBJECT(Type));
};

SvvInternalAction(SvvInternalLexer, SetBracketsType, void, SvvInternalChar Left, SvvInternalChar Right, int Type)
{
	SvvInternalPairMap_Add(Receiver->brackets_map, CHAR_AS_OBJECT(Left), CHAR_AS_OBJECT(Right), INT_AS_OBJECT(Type));
};

SvvInternalAction(SvvInternalLexer, SetDefaultType, void, int Type)
{
	Receiver->default_type = Type;
};

SvvInternalAction(SvvInternalLexer, Destroy, void)
{
	SvvInternalSet_Destroy(Receiver->delimiters_set);
	SvvInternalStringMap_Destroy(Receiver->keywords_map);
	SvvInternalPairMap_Destroy(Receiver->brackets_map);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalRoutine(SvvInternalLexer, DetermineType, void, SvvInternalLexerToken token)
{
	if(SvvInternalStringMap_ExistsKey(Receiver->keywords_map, token->string))
	{
		token->type = OBJECT_AS_INT(SvvInternalStringMap_GetValue(Receiver->keywords_map, token->string));
		return;
	};

	SvvInternalStringIterator first_position = SvvInternalString_GetFirst(token->string);
	SvvInternalStringIterator last_position = SvvInternalString_GetLast(token->string);
	int first_char_code = SvvInternalChar_GetCode(SvvInternalStringIterator_CharGet(first_position));
	int last_char_code = SvvInternalChar_GetCode(SvvInternalStringIterator_CharGet(last_position));
	
	SvvInternalStringIterator_Destroy(first_position);
	SvvInternalStringIterator_Destroy(last_position);
	
	if(SvvInternalPairMap_ExistsKey(Receiver->brackets_map, INT_AS_OBJECT(first_char_code), INT_AS_OBJECT(last_char_code)))
	{
		token->type = OBJECT_AS_INT(SvvInternalPairMap_GetValue(Receiver->brackets_map, 
			INT_AS_OBJECT(first_char_code), INT_AS_OBJECT(last_char_code)));
		return;
	};

	token->type = LEXER_TOKEN_TYPE_FIELD_NAME;
	return;
};


SvvInternalRoutine(SvvInternalLexer, AddToken, void)
{
	SvvInternalLexerToken token = SvvInternalLexerToken_Create();
	token->string = Receiver->to_add;
	SvvInternalLexer_DetermineType(Receiver, token);
	SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(token));
};

SvvInternalRoutine(SvvInternalLexer, DetermineCharType, void)
{
	if(SvvInternalSet_Exists(Receiver->delimiters_set, CHAR_AS_OBJECT(Receiver->being_processed_char)))
	{
		Receiver->being_processed_char_type = LEXER_CHAR_DELIMITER;
		return;
	};
	Receiver->being_processed_char_type = LEXER_CHAR_IDENTIFIER;
};

SvvInternalRoutine(SvvInternalLexer, OnDelimiterMet, void)
{
	switch(Receiver->being_processed_char_type)
	{
		case LEXER_CHAR_IDENTIFIER:
			Receiver->to_add = SvvInternalString_Create();
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->being_processed_char);
			Receiver->state = LEXER_STATE_READING_SYMBOL;
			return;
		case LEXER_CHAR_DELIMITER:
			return;
	};	
};

SvvInternalRoutine(SvvInternalLexer, OnReadingSymbol, void)
{
	switch(Receiver->being_processed_char_type)
	{
		case LEXER_CHAR_IDENTIFIER:
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->being_processed_char);
			return;
		case LEXER_CHAR_DELIMITER:
			SvvInternalLexer_AddToken(Receiver);
			Receiver->state = LEXER_STATE_DELIMITER_MET;
			return;
	};
};

SvvInternalRoutine(SvvInternalLexer, OnEndOfString, void)
{
	if(Receiver->state == LEXER_STATE_READING_SYMBOL)
	{
		SvvInternalLexer_AddToken(Receiver);
	};
};

SvvInternalRoutine(SvvInternalLexer, ProcessChar, void)
{
	SvvInternalLexer_DetermineCharType(Receiver);
	switch(Receiver->state)
	{
		case LEXER_STATE_DELIMITER_MET:
			SvvInternalLexer_OnDelimiterMet(Receiver);
			return;
		case LEXER_STATE_READING_SYMBOL:
			SvvInternalLexer_OnReadingSymbol(Receiver);
			return;
	};
};

SvvInternalAction(SvvInternalLexer, Analyze, SvvInternalList, SvvInternalString String)
{
	Receiver->to_return = SvvInternalList_Create();
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(String);
	Receiver->state = LEXER_STATE_END_OF_SENTENCE_MET;
	while(!SvvInternalStringIterator_EndReached(iterator))
	{
		Receiver->being_processed_char = SvvInternalStringIterator_CharGet(iterator);
		SvvInternalLexer_ProcessChar(Receiver);
		SvvInternalStringIterator_GetNext(iterator);
	};
	SvvInternalLexer_OnEndOfString(Receiver);
	return Receiver->to_return;
};

