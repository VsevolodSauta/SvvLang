#include "internals/globals.h"
#include "internals/machine/interface.h"

#include "internals/list/interface.h"
#include "internals/lexer/interface.h"
#include "internals/string_factory/interface.h"

#include "internals/token/interface.h"

#include "externals/object/interface.h"

SvvInternalCreator(SvvInternalMachine)
{
	SvvInternalMachine machine = OBJECT_AS_LINK(
		SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMachine)));
	machine->base = SvvExternalObject_Create();
	return machine;
};

SvvInternalRoutine(SvvInternalMachine, DestroyLexerOutput, void, SvvInternalList tokens)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(tokens);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalLexerToken token = OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator));
		SvvInternalLexerToken_Destroy(token);
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	SvvInternalList_Destroy(tokens);
};

SvvInternalRoutine(SvvInternalMachine, CreateLexer, SvvInternalLexer)
{
	SvvInternalLexer to_return = SvvInternalLexer_Create();
	SvvInternalLexer_AddDelimiter(to_return, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ' '));
	SvvInternalLexer_AddDelimiter(to_return, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\t'));
	SvvInternalLexer_AddDelimiter(to_return, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '\v'));
	SvvInternalLexer_AddDelimiter(to_return, SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ' '));
	
	SvvInternalTokenFactory token_factory = SvvInternalTokenFactory_Create();
	SvvInternalTokenFactory_SetDefaultType(token_factory, TOKEN_TYPE_IDENTIFIER);
	SvvInternalTokenFactory_SetKeywordType(token_factory, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "method"),
		TOKEN_TYPE_KEYWORD_METHOD); 
	SvvInternalTokenFactory_SetKeywordType(token_factory, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "message"),
		TOKEN_TYPE_KEYWORD_MESSAGE); 
	SvvInternalTokenFactory_SetKeywordType(token_factory, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "property"),
		TOKEN_TYPE_KEYWORD_PROPERTY); 
	SvvInternalTokenFactory_SetKeywordType(token_factory, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "\n"),
		TOKEN_TYPE_END_OF_SENTENCE);
	SvvInternalTokenFactory_SetKeywordType(token_factory, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, ";"),
		TOKEN_TYPE_END_OF_SENTENCE);
	SvvInternalTokenFactory_SetBracketsType(token_factory, 
		SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '<'),
		SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '>'),
		TOKEN_TYPE_FIELD_LINK);
	SvvInternalTokenFactory_SetBracketsType(token_factory, 
		SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, '['),
		SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, ']'),
		TOKEN_TYPE_METHOD_INVOCATION);

	SvvInternalLexer_SetTokenFactory(to_return, token_factory);
	return to_return;
};

SvvInternalAction(SvvInternalMachine, ApplicationCreateFrom, void, SvvInternalString Buffer)
{
	SvvInternalLexer lexer  = SvvInternalMachine_CreateLexer(Receiver);
	SvvInternalList  tokens = SvvInternalLexer_Analyze(lexer, Buffer);
	SvvExternalObject application = SvvExternalObject_Derive(Receiver->base);

	SvvInternalMessage message = SvvInternalMessage_Create();
	
	SvvInternalToken token;
	token = SvvInternalTokenFactory_GetTokenFromASCIIString(SvvDefaultTokenFactory, "Do");
	SvvInternalMessage_TokenAppend(message, token);
	SvvInternalToken_Destroy(token);
	SvvInternalMessage_ListAppend(message, tokens);
	token = SvvInternalTokenFactory_GetTokenFromASCIIString(SvvDefaultTokenFactory, "Receiver");
	SvvInternalMessage_TokenAppend(message, token);
	SvvInternalToken_Destroy(token);
	token = SvvInternalTokenFactory_GetTokenFromASCIIString(SvvDefaultTokenFactory, "Destroy");
	SvvInternalMessage_TokenAppend(message, token);
	SvvInternalToken_Destroy(token);
	token = SvvInternalTokenFactory_GetTokenFromKeywordType(SvvDefaultTokenFactory, TOKEN_TYPE_END_OF_SENTENCE);
	SvvInternalMessage_TokenAppend(message, token);
	SvvInternalToken_Destroy(token);
	
	SvvInternalMachine_DestroyLexerOutput(Receiver);

	SvvExternalObject_SendMessage(application, message);		
};

SvvInternalAction(SvvInternalMachine, Destroy, void)
{
	SvvExternalObject_UnLink(Receiver->base);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

