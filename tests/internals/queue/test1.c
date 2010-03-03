#include "internal_queue.h"
#include "internal_object.h"

#define TESTER_SIZE 100

int main(void)
{
	int i;
	SvvInternalQueue queue = SvvInternalQueue_Create();
	
	for(i = 0; i <= TESTER_SIZE; i++)
	{
		SvvInternalQueue_Push(queue, INT_AS_OBJECT(i));
	};
	
	for(i = 0; i <= TESTER_SIZE; i++)
	{
		if(SvvInternalObject_Compare(SvvInternalQueue_Pop(queue), INT_AS_OBJECT(i)))
		{
			return 1;
		};
	};
	
	SvvInternalQueue_Destroy(queue);
	return 0;
};