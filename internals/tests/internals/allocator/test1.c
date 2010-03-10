#include "internal_allocator.h"
#include "internal_object.h"
#include "internal_globals.h"

int main(void)
{
	SvvInternalObject obj = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, obj);
	return 0;
};