#include "internals/basics.h"
#include "internals/set/interface.h"

int main(void)
{
	SvvInternalObject obj1 = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalObject obj2 = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalObject obj3 = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalObject obj4 = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	
	SvvInternalSet set1 = SvvInternalSet_Create();
	SvvInternalSetIterator iterator;
	
	SvvInternalSet_Add(set1, obj1);
	SvvInternalSet_Add(set1, obj2);
	SvvInternalSet_Add(set1, LINK_AS_OBJECT(set1));
	
	iterator = SvvInternalSet_GetIterator(set1);
	
	
	while(!SvvInternalSetIterator_EndReached(iterator))
	{
		SvvInternalSetIterator_GetNext(iterator);
	};
	SvvInternalSetIterator_Destroy(iterator);
	
	if(!SvvInternalSet_Exists(set1, obj1))
	{
		return 1;
	};
	if(!SvvInternalSet_Exists(set1, LINK_AS_OBJECT(set1)))
	{
		return 1;
	};
	if(SvvInternalSet_Exists(set1, obj3))
	{
		return 1;
	};
	
	return 0;
};