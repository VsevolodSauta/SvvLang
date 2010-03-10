#include "internal_allocator.h"
#include "internal_object.h"
#include "internal_globals.h"
#include "internal_mmu.h"

int main(void)
{
	SvvInternalObject obj = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalObject obj1 = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	SvvInternalMMU_Copy(SvvDefaultMMU, obj1, obj, 10);
	if(SvvInternalMMU_Compare(SvvDefaultMMU, obj1, obj, 10))
		return 1;
	SvvInternalAllocator_Delete(SvvDefaultAllocator, obj);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, obj1);
	return 0;
};