#include "internals/actions.h"
#include "internals/object/interface.h"
#include "internals/mmu/interface.h"

#include "internals/globals.h"

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object)
{
	switch(Receiver.id)
	{
		case OBJECT_ID_LINK:
			return SvvInternalMMU_Compare(SvvDefaultMMU,
				LINK_AS_OBJECT(&(Receiver.ptr_data)),
				LINK_AS_OBJECT(&(Object.ptr_data)),
				sizeof(Object.ptr_data));
		case OBJECT_ID_CHAR:
			return SvvInternalChar_Compare(Receiver.char_data, Object.char_data);
		case OBJECT_ID_INT:
			return (Receiver.int_data > Object.int_data ? 1 :
				(Receiver.int_data < Object.int_data ? -1 : 0));
		default:
			return 0;
	};
};
