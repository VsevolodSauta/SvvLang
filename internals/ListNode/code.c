#include "internals/basics.h"
#include "internals/ListNode/imports.h"

Object ListNode_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct ListNode));
	Object_SetComparator(toReturn, &ListNode_Compare);
	Object_SetDestructor(toReturn, &ListNode_Destroy);
	Object_SetCloner(toReturn, &ListNode_Clone);
	return toReturn;
}


Object ListNode_Clone(Object self)
{
	Object toReturn;
	toReturn = ListNode_Create();
	(((ListNode) (toReturn->entity))->next) = (((ListNode) (self->entity))->next);
	(((ListNode) (toReturn->entity))->prev) = (((ListNode) (self->entity))->prev);
	(((ListNode) (toReturn->entity))->data) = (((ListNode) (self->entity))->data);
	Object_Retain((((ListNode) (toReturn->entity))->data));
	return toReturn;
}

Object ListNode_Compare(Object self, Object listNode)
{
	return Object_Compare(Object_Hash(self), Object_Hash(listNode));
}

Object ListNode_Destroy(Object self)
{
	Object_Release((((ListNode) (self->entity))->data));
	return Object_Destroy(self);
}

