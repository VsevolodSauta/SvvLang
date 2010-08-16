#include "internals/basics.h"
#include "internals/lexer/interface.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"
#include "internals/set/interface.h"
#include "internals/token/interface.h"
#include "internals/token_factory/interface.h"

SvvInternalCreator(SvvInternalLexer)
{
	SvvInternalLexer lexer = 
		OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalLexer)));
	lexer->delimiters_set = SvvInternalSet_Create();
	return lexer;
};

SvvInternalAction(SvvInternalLexer, SetTokenFactory, void, SvvInternalTokenFactory Factory)
{
	Receiver->token_factory = Factory;
};

SvvInternalAction(SvvInternalLexer, AddDelimiter, void, SvvInternalChar Char)
{
	SvvInternalSet_Add(Receiver->delimiters_set, CHAR_AS_OBJECT(Char));
};

SvvInternalAction(SvvInternalLexer, Destroy, void)
{
	SvvInternalSet_Destroy(Receiver->delimiters_set);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};


SvvInternalRoutine(SvvInternalLexer, AddToken, void)
{
	SvvInternalToken token = SvvInternalTokenFactory_GetTokenFromString(Receiver->token_factory, Receiver->to_add);
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
//	DEBUG("Char '%c', type %i, state %i.\n", Receiver->being_processed_char.bytes[0], 
//		Receiver->being_processed_char_type, Receiver->state);
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
	Receiver->state = LEXER_STATE_DELIMITER_MET;
	while(!SvvInternalStringIterator_EndReached(iterator))
	{
		Receiver->being_processed_char = SvvInternalStringIterator_CharGet(iterator);
		SvvInternalLexer_ProcessChar(Receiver);
		SvvInternalStringIterator_GetNext(iterator);
	};
	SvvInternalLexer_OnEndOfString(Receiver);
	return Receiver->to_return;
};

