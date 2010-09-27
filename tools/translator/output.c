typedef struct ListNode {
	Object next;
	Object prev;
	Object data;
} *ListNode;

typedef struct ListIterator {
	Object list;
	Object node;
} *ListIterator;

typedef struct List {
	Object iterator;
	Object head;
	Object tail;
} *List;


Object List_Search(Object self, Object object)
{
	Object iterator;
	iterator = ENTITY(self, List)->iterator;
	ListIterator_ToBegin(iterator);
	Object list;
	list = Object_Autorelease(List_Create());
	ListIterator_SearchFirst(iterator, object);
	while(ListIterator_ThisEnd(iterator) == false)
	{
		Object_PushBack(list, Object_TempClone(iterator));
		ListIterator_SearchFirst(iterator, object);
	}
	return list;
}


Object List_Size(Object self)
{
	ListIterator_ToBegin(ENTITY(self, List)->iterator);
	Object toReturn;
	toReturn = NumberFactory_FromLong(numberFactory, 0);
	while(ListIterator_ThisEnd(ENTITY(self, List)->iterator) == false)
	{
		Number_Inc(toReturn);
		ListIterator_Next(ENTITY(self, List)->iterator);
	}
	ListIterator_Hide(ENTITY(self, List)->iterator);
	return toReturn;
}


Object List_Concatenate(Object self, Object list)
{
	ListIterator_ToEnd(ENTITY(self, List)->iterator);
	ListIterator_AddListAfter(ENTITY(self, List)->iterator, list);
	ListIterator_Hide(ENTITY(self, List)->iterator);
	return self;
}


Object List_SublistBetweenIterators(Object self, Object positionFrom, Object positionTo)
{
	Object iterator;
	iterator = Object_Clone(positionFrom);
	Object list;
	list = List_Create();
	while(Object_Compare(iterator, positionTo) != equal)
	{
		List_PushBack(list, ENTITY(ENTITY(iterator, ListIterator)->node, ListNode)->data);
		ListIterator_Next(iterator);
	}
	Object_Release(iterator);
	return list;
}

