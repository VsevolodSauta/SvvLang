#include "internals/lexer/interface.h"
#include "internals/string/interface.h"
#include "internals/char_factory/interface.h"
#include "internals/globals.h"

int main(void)
{
	SvvInternalString string = SvvInternalString_Create();
	SvvInternalString_CharAppend(string, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'a'));
	SvvInternalString_CharAppend(string, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'b'));
	SvvInternalString_CharAppend(string, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'a'));
	SvvInternalString_CharAppend(string, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ' '));
	
	SvvInternalString_Concatenate(string, string);
	SvvInternalString_Concatenate(string, string);
	
	SvvInternalString_CharSetAt(string, 5, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'c'));
	SvvInternalString_CharSetAt(string, 9, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'd'));
	SvvInternalString_CharSetAt(string, 13, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 'e'));
	
	SvvInternalLexer lexer = SvvInternalLexer_Create();
	SvvInternalList list = SvvInternalLexer_Analyze(lexer, string);
	
//	DEBUG("String: \"%s\".\n", string->data->data);
//	DEBUG("Tokens list: ");
//	SvvInternalList_Dump(list);
//	SvvInternalListIterator iterator = SvvInternalList_GetFirst(list);
//	while(!SvvInternalListIterator_EndReached(iterator))
//	{
//		SvvInternalUArray uarray = SvvInternalString_GetUArray(OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator)));
//		DEBUG("String: \"%s\"\n", uarray->data);
//		SvvInternalUArray_Destroy(uarray);
//		SvvInternalListIterator_GetNext(iterator);
//	};
//	SvvInternalListIterator_Destroy(iterator);
//	DEBUG("Tokens in list %i", SvvInternalList_GetSize(list));
	TEST("Tokens in list check", SvvInternalList_GetSize(list) == 5);
	
	SvvInternalLexer_Destroy(lexer);
	SvvInternalString_Destroy(string);
	SvvInternalList_Destroy(list);
	return 0;
};
