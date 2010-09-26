#include "internals/stack/interface.h"
#include "internals/object/interface.h"

#define TESTER_SIZE 100

int main(void)
{
	INIT();
	int i;
	Object stack = Stack_Create();
	
	for(i = 0; i <= TESTER_SIZE; i++)
	{
		Stack_Push(stack, INT_AS_OBJECT(i));
	};
	
	for(i =  TESTER_SIZE; i >= 0; i--)
	{
		if(Object_Compare(Stack_Pop(stack), INT_AS_OBJECT(i)) != equal)
		{
			return 1;
		};
	};
	
	Object_Release(stack);
	return 0;
};