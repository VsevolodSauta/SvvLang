#include "internals/basics.h"
#include "internals/string_map/element.h"

#include "internals/string/interface.h"

SvvInternalCreator(SvvInternalStringMapIteratorElement)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringMapIteratorElement)));
};

SvvInternalAction(SvvInternalStringMapIteratorElement, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringMapIteratorElement, Clone, SvvInternalStringMapIteratorElement)
{
	SvvInternalStringMapIteratorElement element = SvvInternalStringMapIteratorElement_Create();
	element->string = SvvInternalString_Clone(Receiver->string);
	element->node = Receiver->node;
	return element;
};

