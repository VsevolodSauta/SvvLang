#include "internals/basics.h"

#include "internals/list/node.h"

#define ListNode_GID 0x40

Defaults(ListNode);

Action(ListNode, Clone)
{
	Object toReturn = ListNode_Create();
	NEXT(toReturn) = NEXT(receiver);
	PREV(toReturn) = PREV(receiver);
	Object_Retain(DATA(toReturn) = DATA(receiver));
	return toReturn;
};

Action(ListNode, Compare, Object compareTo)
{
	if(ENTITY(receiver, ListNode) > ENTITY(compareTo, ListNode))
		return greater;
	if(ENTITY(receiver, ListNode) < ENTITY(compareTo, ListNode))
		return less;
	return equal;
};

Action(ListNode, Destroy)
{
	Object_Release(DATA(receiver));
	return Object_Destroy(receiver);
};
