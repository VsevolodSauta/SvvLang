#include "internals/basics.h"

int main(void)
{
	Object obj = Object_Create();
	DEBUG("Allocated...");
	Object_Release(obj);
	DEBUG(" deleted.\n");
	return 0;
};