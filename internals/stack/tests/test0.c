#include "internals/stack/interface.h"
#include "internals/object/interface.h"

#define TESTER_SIZE 100

int main(void)
{
	int i;
	SvvInternalStack stack = SvvInternalStack_Create();
	
	for(i = 0; i <= TESTER_SIZE; i++)
	{
		SvvInternalStack_Push(stack, INT_AS_OBJECT(i));
	};
	
	for(i =  TESTER_SIZE; i >= 0; i--)
	{
		if(SvvInternalObject_Compare(SvvInternalStack_Pop(stack), INT_AS_OBJECT(i)))
		{
			return 1;
		};
	};
	
	SvvInternalStack_Destroy(stack);
	return 0;
};