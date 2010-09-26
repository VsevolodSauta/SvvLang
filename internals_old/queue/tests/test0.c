#include "internals/queue/interface.h"
#include "internals/object/interface.h"
#include "internals/debugger.h"

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
		SvvInternalObject object = SvvInternalQueue_Pop(queue);
//		DEBUG("%i ", OBJECT_AS_INT(object));
		if(SvvInternalObject_Compare(object, INT_AS_OBJECT(i)))
		{
			return 1;
		};
	};
	DEBUG("\n");
	SvvInternalQueue_Destroy(queue);
	return 0;
};
