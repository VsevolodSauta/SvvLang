#include "internals/basics.h"
#include "internals/lexer/interface.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"
#include "internals/set/interface.h"

SvvInternalCreator(SvvInternalLexer)
{
	SvvInternalLexer lexer = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalLexer)));
	lexer->set_of_delimiters = SvvInternalSet_Create();
	lexer->end_of_sentence_char = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\n');
	SvvInternalSet_Add(lexer->set_of_delimiters, CHAR_AS_OBJECT(SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ' ')));
	SvvInternalSet_Add(lexer->set_of_delimiters, CHAR_AS_OBJECT(SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\t')));
	return lexer;
};

SvvInternalAction(SvvInternalLexer, Destroy, void)
{
	SvvInternalSet_Destroy(Receiver->set_of_delimiters);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalLexer, DetermineCharType, void)
{
	if(SvvInternalSet_Exists(Receiver->set_of_delimiters, CHAR_AS_OBJECT(Receiver->processing_char)))
	{
		Receiver->processing_char_type = LEXER_CHAR_DELIMITER;
		return;
	};
	if(SvvInternalChar_Compare(Receiver->processing_char, Receiver->end_of_sentence_char) == 0)
	{
		Receiver->processing_char_type = LEXER_CHAR_END_OF_SENTENCE;
		return;
	};
	Receiver->processing_char_type = LEXER_CHAR_IDENTIFIER;
};

SvvInternalAction(SvvInternalLexer, OnDelimiterMet, void)
{
	switch(Receiver->processing_char_type)
	{
		case LEXER_CHAR_IDENTIFIER:
			Receiver->to_add = SvvInternalString_Create();
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->processing_char);
			Receiver->state = LEXER_STATE_READING_SYMBOL;
			return;
		case LEXER_CHAR_DELIMITER:
		case LEXER_CHAR_END_OF_SENTENCE:
			return;
	};	
};

SvvInternalAction(SvvInternalLexer, OnReadingSymbol, void)
{
	switch(Receiver->processing_char_type)
	{
		case LEXER_CHAR_IDENTIFIER:
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->processing_char);
			return;
		case LEXER_CHAR_DELIMITER:
			SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(Receiver->to_add));
			Receiver->state = LEXER_STATE_DELIMITER_MET;
			return;
		case LEXER_CHAR_END_OF_SENTENCE:
			SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(Receiver->to_add));
			Receiver->to_add = SvvInternalString_Create();
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->end_of_sentence_char);
			SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(Receiver->to_add));
			Receiver->state = LEXER_STATE_END_OF_SENTENCE_MET;
			return;
	};
};

SvvInternalAction(SvvInternalLexer, OnEndOfSentenceMet, void)
{
	switch(Receiver->processing_char_type)
	{
		case LEXER_CHAR_IDENTIFIER:
			Receiver->to_add = SvvInternalString_Create();
			SvvInternalString_CharAppend(Receiver->to_add, Receiver->processing_char);
			Receiver->state = LEXER_STATE_READING_SYMBOL;
			return;
		case LEXER_CHAR_DELIMITER:
		case LEXER_CHAR_END_OF_SENTENCE:
			return;
	};
};

SvvInternalAction(SvvInternalLexer, OnEndOfString, void)
{
	DEBUG("End of string. State: %i.\n", Receiver->state);
	if(Receiver->state == LEXER_STATE_READING_SYMBOL)
	{
		SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(Receiver->to_add));
	};
	if(Receiver->state != LEXER_STATE_END_OF_SENTENCE_MET)
	{
		Receiver->to_add = SvvInternalString_Create();
		SvvInternalString_CharAppend(Receiver->to_add, Receiver->end_of_sentence_char);
		SvvInternalList_PushBack(Receiver->to_return, LINK_AS_OBJECT(Receiver->to_add));
	};
};

SvvInternalAction(SvvInternalLexer, ProcessChar, void)
{
	SvvInternalLexer_DetermineCharType(Receiver);
	DEBUG("Char: \"%c\". Type: %i. State: %i.\n", Receiver->processing_char.bytes[0], Receiver->processing_char_type, Receiver->state);
	switch(Receiver->state)
	{
		case LEXER_STATE_DELIMITER_MET:
			SvvInternalLexer_OnDelimiterMet(Receiver);
			return;
		case LEXER_STATE_READING_SYMBOL:
			SvvInternalLexer_OnReadingSymbol(Receiver);
			return;
		case LEXER_STATE_END_OF_SENTENCE_MET:
			SvvInternalLexer_OnEndOfSentenceMet(Receiver);
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
		Receiver->processing_char = SvvInternalStringIterator_CharGet(iterator);
		SvvInternalLexer_ProcessChar(Receiver);
		SvvInternalStringIterator_GetNext(iterator);
	};
	SvvInternalLexer_OnEndOfString(Receiver);
	return Receiver->to_return;
};

