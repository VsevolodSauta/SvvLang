typedef struct ListNode {
	Object _next;
	Object _prev;
	Object _data;
} *ListNode;

Object ListNode_Create(void);
Object ListNode_Clone(Object _self);
Object ListNode_Compare(Object _self, Object _listNode);
Object ListNode_Destroy(Object _self);
