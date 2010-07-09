#include "internals/basics.h"
#include "internals/string_set/interface.h"
#include "internals/string_set/node.h"

#include "internals/stack/interface.h"
#include "internals/injection/interface.h"
#include "internals/string/interface.h"


SvvInternalCreator(SvvInternalStringSetIterator)
{
	SvvInternalStringSetIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSetIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalStringSetIterator, GetNext, void)
{
	while(1)
	{
		if(!IS_NOTHING(Receiver->element))
		{
			SvvInternalStringSetIteratorElement_Destroy(Receiver->element);
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
				SvvInternalStringSetIteratorElement element = SvvInternalStringSetIteratorElement_Create();
				element->node = OBJECT_AS_LINK(SvvInternalInjectionIterator_GetValue(iterator));
				element->string = SvvInternalString_Clone(Receiver->element->string);
				SvvInternalString_CharAppend(element->string, OBJECT_AS_CHAR(SvvInternalInjectionIterator_GetKey(iterator)));
				SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
				SvvInternalInjectionIterator_GetNext(iterator);
			};
			SvvInternalInjectionIterator_Destroy(iterator);
			if(SvvInternalStringSetNode_IsSet(Receiver->element->node))
			{
				break;
			};
		};
	};
};

SvvInternalAction(SvvInternalStringSetIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->element);
};

SvvInternalAction(SvvInternalStringSetIterator, GetData, SvvInternalString)
{
	return SvvInternalString_Clone(Receiver->element->string);
};

SvvInternalAction(SvvInternalStringSetIterator, Destroy, void)
{
	while(!SvvInternalStack_IsEmpty(Receiver->path))
	{
		SvvInternalStringSetIteratorElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalStringSetIteratorElement_Destroy(element);
	};
	SvvInternalStringSetIteratorElement_Destroy(Receiver->element);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringSetIterator, Clone, SvvInternalStringSetIterator)
{
	SvvInternalStack intermediate_stack = SvvInternalStack_Create();
	SvvInternalStringSetIterator iterator = SvvInternalStringSetIterator_Create();
	
	while(!SvvInternalStack_IsEmpty(Receiver->path)){
		SvvInternalStack_Push(intermediate_stack, SvvInternalStack_Pop(Receiver->path));
	};
	
	while(!SvvInternalStack_IsEmpty(intermediate_stack)){
		SvvInternalStringSetIteratorElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(intermediate_stack));
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
		SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(SvvInternalStringSetIteratorElement_Clone(element)));
	};
	
	iterator->element = SvvInternalStringSetIteratorElement_Clone(Receiver->element);
	SvvInternalStack_Destroy(intermediate_stack);
	return iterator;
};

