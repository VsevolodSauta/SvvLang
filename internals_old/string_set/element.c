#include "internals/basics.h"
#include "internals/string_set/element.h"

#include "internals/string/interface.h"

SvvInternalCreator(SvvInternalStringSetIteratorElement)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSetIteratorElement)));
};

SvvInternalAction(SvvInternalStringSetIteratorElement, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringSetIteratorElement, Clone, SvvInternalStringSetIteratorElement)
{
	SvvInternalStringSetIteratorElement element = SvvInternalStringSetIteratorElement_Create();
	element->string = SvvInternalString_Clone(Receiver->string);
	element->node = Receiver->node;
	return element;
};

