#include "internals/object/interface.h"
#include "internals/set/interface.h"

SvvInternalSet set1;
SvvInternalSetIterator iterator;

void DumpTree(void)
{
	iterator = SvvInternalSet_GetIterator(set1);
	while(!SvvInternalSetIterator_EndReached(iterator))
	{
		SvvInternalSetIterator_GetNext(iterator);
	};
	SvvInternalSetIterator_Destroy(iterator);
};

int main(void)
{
	set1 = SvvInternalSet_Create();
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(500));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(300));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(100));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(200));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(700));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(600));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(900));
	DumpTree();
	SvvInternalSet_Add(set1, INT_AS_OBJECT(800));
	DumpTree();
	SvvInternalSet_Destroy(set1);
	return 0;
};