#include "internals/basics.h"
#include "internals/ListNode/imports.h"

typedef struct ListNode {
	Object next;
	Object prev;
	Object data;
} *ListNode;

