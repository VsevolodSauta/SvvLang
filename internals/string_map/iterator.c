#include "internals/basics.h"
#include "internals/string_map/interface.h"
#include "internals/string_map/node.h"

#include "internals/stack/interface.h"
#include "internals/injection/interface.h"
#include "internals/string/interface.h"


SvvInternalCreator(SvvInternalStringMapIterator)
{
	SvvInternalStringMapIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringMapIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalStringMapIterator, GetNext, void)
{
	while(1)
	{
		if(!IS_NOTHING(Receiver->element))
		{
			SvvInternalStringMapIteratorElement_Destroy(Receiver->element);
		};
		
		if(SvvInternalStack_IsEmpty(Receiver->path))
		{
			Receiver->element = OBJECT_AS_LINK(SvvInternalNothing);
			break;
		} else {
			Receiver->element = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
			SvvInternalInjectionIterator iterator = SvvInternalInjection_GetIterator(Receiver->element->node->next_char);
			while(!SvvInternalInjectionIterator_EndReached(iterator))
			{
				SvvInternalStringMapIteratorElement element = SvvInternalStringMapIteratorElement_Create();
				element->node = OBJECT_AS_LINK(SvvInternalInjectionIterator_GetValue(iterator));
				element->string = SvvInternalString_Clone(Receiver->element->string);
				SvvInternalString_CharAppend(element->string, OBJECT_AS_CHAR(SvvInternalInjectionIterator_GetKey(iterator)));
				SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
				SvvInternalInjectionIterator_GetNext(iterator);
			};
			SvvInternalInjectionIterator_Destroy(iterator);
			if(SvvInternalStringMapNode_IsMapped(Receiver->element->node))
			{
				break;
			};
		};
	};
};

SvvInternalAction(SvvInternalStringMapIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->element);
};

SvvInternalAction(SvvInternalStringMapIterator, GetKey, SvvInternalString)
{
	return SvvInternalString_Clone(Receiver->element->string);
};

SvvInternalAction(SvvInternalStringMapIterator, GetValue, SvvInternalObject)
{
	return Receiver->element->node->value;
};

SvvInternalAction(SvvInternalStringMapIterator, Destroy, void)
{
	while(!SvvInternalStack_IsEmpty(Receiver->path))
	{
		SvvInternalStringMapIteratorElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalStringMapIteratorElement_Destroy(element);
	};
	SvvInternalStringMapIteratorElement_Destroy(Receiver->element);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringMapIterator, Clone, SvvInternalStringMapIterator)
{
	SvvInternalStack intermediate_stack = SvvInternalStack_Create();
	SvvInternalStringMapIterator iterator = SvvInternalStringMapIterator_Create();
	
	while(!SvvInternalStack_IsEmpty(Receiver->path)){
		SvvInternalStack_Push(intermediate_stack, SvvInternalStack_Pop(Receiver->path));
	};
	
	while(!SvvInternalStack_IsEmpty(intermediate_stack)){
		SvvInternalStringMapIteratorElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(intermediate_stack));
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
		SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(SvvInternalStringMapIteratorElement_Clone(element)));
	};
	
	iterator->element = SvvInternalStringMapIteratorElement_Clone(Receiver->element);
	SvvInternalStack_Destroy(intermediate_stack);
	return iterator;
};

