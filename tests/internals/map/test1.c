#include "internal_map.h"
#include "internal_debugger.h"

/*
SvvInternalCreator(SvvInternalMap);
SvvInternalAction(SvvInternalMap, Destroy, void);
SvvInternalAction(SvvInternalMap, Add, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalMap, RemoveKey, void, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, ExistsKey, int, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, GetValue, SvvInternalObject, SvvInternalObject Key);
*/

int main(void)
{
	int i;
	SvvInternalMap map = SvvInternalMap_Create();
	
	for(i = 0; i < 100; i++)
	{
		SvvInternalMap_Add(map, INT_AS_OBJECT(i), INT_AS_OBJECT(i * 2));
	};
	for(i = 0; i < 100; i += 2)
	{
		SvvInternalMap_RemoveKey(map, INT_AS_OBJECT(i));
	};
	for(i = 0; i < 100; i++)
	{
		if(SvvInternalMap_ExistsKey(map, INT_AS_OBJECT(i)) != (i & 1))
		{
			DEBUG("Key %i doesn't exist.\n", i);
			return 1;
		};
	};
	for(i = 1; i < 100; i += 2)
	{
		if(OBJECT_AS_INT(SvvInternalMap_GetValue(map, INT_AS_OBJECT(i))) != (i * 2))
		{
			DEBUG("Value of key %i is %i.\n", i, OBJECT_AS_INT(SvvInternalMap_GetValue(map, INT_AS_OBJECT(i))));
			return 1;
		};
	};
	
	
	SvvInternalMap_Destroy(map);
	return 0;
};
