typedef struct ListNode {
	Object next;
	Object prev;
	Object data;
} *ListNode;
Object ListNode_Clone(Object self);
Object ListNode_Compare(Object self, Object listNode);
Object ListNode_Destroy(Object self);
