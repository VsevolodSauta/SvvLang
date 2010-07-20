#include "internals/globals.h"
#include "internals/machine/interface.h"

#include "internals/list/interface.h"
#include "internals/lexer/interface.h"
#include "internals/string_factory/interface.h"

#include "externals/object/interface.h"

SvvInternalCreator(SvvInternalMachine)
{
	SvvInternalMachine machine = OBJECT_AS_LINK(
		SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMachine)));
	machine->prototype = SvvExternalObject_Create();
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
	return to_return;
};

SvvInternalAction(SvvInternalMachine, Execute, void, SvvInternalString Buffer)
{
	SvvInternalLexer lexer  = SvvInternalMachine_CreateLexer(Receiver);
	SvvInternalList  tokens = SvvInternalLexer_Analyze(lexer, Buffer);
	SvvExternalObject application = SvvExternalObject_Derive(Receiver->prototype);
	SvvExternalObject_CodeSet(application, tokens);
	SvvExternalObject_PropertySet(application, 
		SvvInternalStringFactory_GetFromASCIIString(SvvDefaultStringFactory, "ApplicationObject"));
	SvvExternalObject_Run(application);
};

SvvInternalAction(SvvInternalMachine, Destroy, void)
{
	SvvExternalObject_UnLink(Receiver->prototype);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

