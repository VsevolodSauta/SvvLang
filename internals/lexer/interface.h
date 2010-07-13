#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"
#include "internals/set/interface.h"

#define LEXER_CHAR_DELIMITER 1
#define LEXER_CHAR_IDENTIFIER 2
#define LEXER_CHAR_END_OF_SENTENCE 3

#define LEXER_STATE_DELIMITER_MET 1
#define LEXER_STATE_READING_SYMBOL 2
#define LEXER_STATE_END_OF_SENTENCE_MET 3


typedef struct SvvInternalLexer {
	int				state;
	SvvInternalString		to_add;
	SvvInternalList			to_return;
	SvvInternalChar			processing_char;
	int				processing_char_type;
	SvvInternalChar			end_of_sentence_char;
	SvvInternalSet			set_of_delimiters;
} *SvvInternalLexer;

SvvInternalCreator(SvvInternalLexer);
SvvInternalAction(SvvInternalLexer, Destroy, void);

SvvInternalAction(SvvInternalLexer, Analyze, SvvInternalList, SvvInternalString String);
