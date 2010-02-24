#include "internal_actions.h"
#include "internal_object.h"
#include "interanal_list.h"
#include "interanal_set.h"

SvvInternalCreator(SvvInternalSetNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalSetNode*)));
};

SvvInternalCreator(SvvInternalSet)
{
	SvvInternalSet set = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalSet*)));
	set->root = OBJECT_AS_LINK(SvvInternalNothing);
	return set;
};

SvvInternalAction(SvvInternalSet, Destroy, void)
{
	SvvInternalSetNode_DestroySubTree(Receiver->root);
};

SvvInternalAction(SvvInternalSet, Add, void, SvvInternalObject Object)
{
	
};

SvvInternalAction(SvvInternalSet, Remove, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Exists, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalSet, AddList, void, SvvInternalList List);
