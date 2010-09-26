#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

typedef struct ListNode {
	Object			next;
	Object			prev;
	Object			data;
} *ListNode;

#define NEXT(receiver) (ENTITY(receiver, ListNode)->next)
#define PREV(receiver) (ENTITY(receiver, ListNode)->prev)
#define DATA(receiver) (ENTITY(receiver, ListNode)->data)

Creator(ListNode);
