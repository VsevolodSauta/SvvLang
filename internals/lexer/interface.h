#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"
#include "internals/set/interface.h"
#include "internals/pair_map/interface.h"
#include "internals/lexer/token.h"

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
	SvvInternalChar			being_processed_char;
	int				being_processed_char_type;
	SvvInternalPairMap		brackets_map;
	SvvInternalStringMap		keywords_map;
	SvvInternalSet			delimiters_set;
	int				default_type;
} *SvvInternalLexer;

SvvInternalCreator(SvvInternalLexer);
SvvInternalAction(SvvInternalLexer, Destroy, void);
SvvInternalAction(SvvInternalLexer, Analyze, SvvInternalList, SvvInternalString String);
SvvInternalAction(SvvInternalLexer, SetKeywordType, void, SvvInternalString String, int Type);
SvvInternalAction(SvvInternalLexer, AddDelimiter, void, SvvInternalChar Char);
SvvInternalAction(SvvInternalLexer, SetBracketsType, void, SvvInternalChar Left, SvvInternalChar Right, int Type);
SvvInternalAction(SvvInternalLexer, SvvDefaultType, void, int Type);
