#include "internals/object/interface.h"
#include "internals/set/interface.h"
#include "internals/list/interface.h"

int main(void)
{
	SvvInternalSet set1;
	SvvInternalList list1;
	SvvInternalSetIterator iterator;

	set1 = SvvInternalSet_Create();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(500));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(300));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(100));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(200));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(700));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(600));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(900));
	SvvInternalSet_Add(set1, INT_AS_OBJECT(800));
	
	list1 = SvvInternalSet_GetList(set1);
	SvvInternalList_Dump(list1);
	SvvInternalSet_Dump(set1);
	SvvInternalList_Destroy(list1);
	
	SvvInternalSet_Destroy(set1);
	return 0;
};