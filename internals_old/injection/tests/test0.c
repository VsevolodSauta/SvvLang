#include "internals/injection/interface.h"

/*
SvvInternalCreator(SvvInternalInjection);
SvvInternalAction(SvvInternalInjection, Destroy, void);
SvvInternalAction(SvvInternalInjection, Add, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalInjection, RemoveKey, void, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjection, ExistsKey, int, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjection, GetValue, SvvInternalObject, SvvInternalObject Key);
*/

int main(void)
{
	int i;
	SvvInternalInjection map = SvvInternalInjection_Create();
	
	for(i = 0; i < 100; i++)
	{
		SvvInternalInjection_Add(map, INT_AS_OBJECT(i), INT_AS_OBJECT(i * 2));
	};
	for(i = 0; i < 100; i += 2)
	{
		SvvInternalInjection_RemoveKey(map, INT_AS_OBJECT(i));
	};
	for(i = 0; i < 100; i++)
	{
		if(SvvInternalInjection_ExistsKey(map, INT_AS_OBJECT(i)) != (i & 1))
		{
			return 1;
		};
	};
	for(i = 1; i < 100; i += 2)
	{
		if(OBJECT_AS_INT(SvvInternalInjection_GetValue(map, INT_AS_OBJECT(i))) != (i * 2))
		{
			return 1;
		};
	};
	
	
	SvvInternalInjection_Destroy(map);
	return 0;
};
