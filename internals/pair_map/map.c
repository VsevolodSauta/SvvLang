#include "internals/basics.h"
#include "internals/map/interface.h"
#include "internals/pair_map/interface.h"

SvvInternalCreator(SvvInternalPairMap)
{
	return SvvInternalMap_Create();
};

SvvInternalAction(SvvInternalPairMap, Destroy, void)
{
	SvvInternalPairMap_Clean(Receiver);
	SvvInternalMap_Destroy(Receiver);
};

SvvInternalAction(SvvInternalPairMap, Add, void, SvvInternalObject Key1, SvvInternalObject Key2, SvvInternalObject Value)
{
	SvvInternalMap second_map;
	if(!SvvInternalMap_ExistsKey(Receiver, Key1))
	{
		second_map = SvvInternalMap_Create();
		SvvInternalMap_Add(Receiver, Key1, LINK_AS_OBJECT(second_map));
	} else {
		second_map = OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver, Key1));
	};
	
	SvvInternalMap_Add(second_map, Key2, Value);
};
SvvInternalAction(SvvInternalPairMap, RemoveKey, void, SvvInternalObject Key1, SvvInternalObject Key2)
{
	SvvInternalMap second_map = OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver, Key1));
	SvvInternalMap_RemoveKey(second_map, Key2);
	if(SvvInternalMap_GetCapacity(second_map) == 0)
	{
		SvvInternalMap_RemoveKey(Receiver, Key1);
	};
};

SvvInternalAction(SvvInternalPairMap, Clean, void)
{
	SvvInternalMapIterator iterator = SvvInternalMap_GetIterator(Receiver);
	while(!SvvInternalMapIterator_EndReached(iterator))
	{
		SvvInternalMap_Destroy(OBJECT_AS_LINK(SvvInternalMapIterator_GetValue(iterator)));
		SvvInternalMapIterator_GetNext(iterator);
	};
	SvvInternalMapIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalPairMap, ExistsKey, int, SvvInternalObject Key1, SvvInternalObject Key2)
{
	if(!SvvInternalMap_ExistsKey(Receiver, Key1))
	{
		return 0;
	} else {
		return SvvInternalMap_ExistsKey(OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver, Key1)), Key2);
	};
};

SvvInternalAction(SvvInternalPairMap, GetValue, SvvInternalObject, SvvInternalObject Key1, SvvInternalObject Key2)
{
	return SvvInternalMap_GetValue(OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver, Key1)), Key2);
};