#include "internals/lexer/interface.h"
#include "internals/string/interface.h"
#include "internals/char_factory/interface.h"
#include "internals/token/interface.h"
#include "internals/string_factory/interface.h"
#include "internals/globals.h"

int main(void)
{
	DEBUG("Creating string.\n");
	SvvInternalString string = 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "aba aca ada aea afa \n");
	
	DEBUG("Creating lexer.\n");
	SvvInternalLexer lexer = SvvInternalLexer_Create();
	DEBUG("Creating token factory.\n");
	SvvInternalTokenFactory token_factory = SvvInternalTokenFactory_Create();
	DEBUG("Attaching token factory.\n");
	SvvInternalLexer_SetTokenFactory(lexer, token_factory);
	DEBUG("Adding delimiters to lexer's set.\n");
	SvvInternalLexer_AddDelimiter(lexer, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\t'));
	SvvInternalLexer_AddDelimiter(lexer, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ' '));
	SvvInternalLexer_AddDelimiter(lexer, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\t'));
	DEBUG("Starting anlysis.\n");
	SvvInternalList list = SvvInternalLexer_Analyze(lexer, string);
	
	DEBUG("String: \"%s\".\n", string->data->data);
	DEBUG("Tokens list: ");
	SvvInternalList_Dump(list);
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(list);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalUArray uarray = SvvInternalString_GetUArray(
			((SvvInternalToken) OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator)))->string
		);
		DEBUG("String: \"%s\"\n", uarray->data);
		SvvInternalUArray_Destroy(uarray);
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	DEBUG("Tokens in list %i\n", SvvInternalList_GetSize(list));
	TEST("Tokens in list check", SvvInternalList_GetSize(list) == 6);
	
	SvvInternalLexer_Destroy(lexer);
	SvvInternalString_Destroy(string);
	SvvInternalList_Destroy(list);
	return 0;
};
