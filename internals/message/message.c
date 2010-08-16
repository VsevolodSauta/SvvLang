#include "internals/basics.h"
#include "internals/message/interface.h"
#include "internals/list/interface.h"
#include "internals/token/interface.h"

SvvInternalCreator(SvvInternalMessage)
{
	SvvInternalMessage message = 
		OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMessage)));
	message->tokens = SvvInternalList_Create();
};

SvvInternalAction(SvvInternalMessage, Destroy, void)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver->tokens);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalToken token = OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator));
		SvvInternalToken_Destroy(token);
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalList_Destroy(Receiver->tokens);
};

SvvInternalAction(SvvInternalMessage, TokenAppend, void, SvvInternalToken Token)
{
	SvvInternalList_PushBack(Receiver->tokens, LINK_AS_OBJECT(SvvInternalToken_Clone(Tokens)));
};

SvvInternalAction(SvvInternalMessage, ListAppend, void, SvvInternalList List)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver->tokens);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalToken token = OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator));
		SvvInternalToken cloned_token = SvvInternalToken_Clone(token);
		SvvInternalList_PushBack(Receiver->tokens LINK_AS_OBJECT(cloned_token));
		SvvInternalListIterator_GetNext(iterator);
	};
};
