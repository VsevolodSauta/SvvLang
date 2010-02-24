#include "internal_action.h"
#include "internal_allocator.h"
#include "internal_list.h"

SvvInternalAction(SvvInternalMachine, Create, SvvInternalMachine)
{
	SvvInternalMachine machine = SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalMachine*));
	machine->objects = SvvInternalList_New(Receiver);
	return machine;
};

SvvInternalAction(SvvInternalMachine, Run, char* Buffer){
	
};

SvvInternalAction(SvvInternalMachine, Destroy)
{
	SvvInternalListIterator iterator1 = SvvInternalList_GetIterator(Receiver->objects);
	while(iterator1 != SvvInternalNothing)
	{
		SvvExternalObject_Unlink(SvvInternalListIterator_GetData(iterator1));
		iterator1 = SvvInternalListIterator_GetNext(iterator1);
	};
	SvvInternalList_Destroy(Receiver->objects);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, Receiver);
};
