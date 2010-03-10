#include "internal_actions.h"
#include "external_object.h"
#include "internal_map.h"
#include "internal_globals.h"

SvvInternalAction(SvvExternalObject, Create, SvvExternalObject)
{
	SvvExternalObject object = SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvExternalObject*));

	object->used  = 0;
	object->ptr_entity = 0;
	object->entity = SvvInternalNothing;
	object->methods = SvvInternalMap_Create(SvvInternalNothing);
	object->messages = SvvInternalMap_Create(SvvInternalNothing);
	object->internals = SvvInternalMap_Create(SvvInternalNothing);

	return object;
};

SvvInternalAction(SvvExternalObject, Destroy, void)
{
	SvvInternalMap map = Receiver->internals;
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(map->values);
	while(iterator != SvvInternalNothing)
	{
		SvvExternalObject_Unlink(SvvInternalListIterator_GetData(iterator));
	};
	SvvInternalMap_Destroy(Receiver->internals);
	SvvInternalMap_Destroy(Receiver->messages);
	SvvInternalMap_Destroy(Receiver->methods);
	if(Receiver->ptr_entity)
	{
		SvvInternalAllocator_Delete(SvvDefaultAllocator, Receiver->entity);
	};
	SvvInternalAllocator_Delete(SvvDefaultAllocator, Receiver);
};

SvvInternalAction(SvvExternalObject, Link, void)
{
	Receiver->used++;
};


SvvInternalAction(SvvExternalObject, Unlink, void)
{
	Receiver->used--;
	if(!Receiver->used)
	{
		SvvExternalObject_Destroy(Receiver);
	};
};
