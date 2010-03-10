#include "internals/basics.h"
#include "internals/set/node.h"

#define INITED_FLAG 1

SvvInternalCreator(SvvInternalSetNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalSetNode)));
};

SvvInternalAction(SvvInternalSetNode, Init, void, SvvInternalObject Object)
{
	Receiver->data = Object;
	Receiver->left = SvvInternalSetNode_Create();
	Receiver->right = SvvInternalSetNode_Create();
	SvvInternalSetNode_DeInit(Receiver->left);
	SvvInternalSetNode_DeInit(Receiver->right);
	Receiver->left->parent = Receiver->right->parent = Receiver;
	Receiver->flags |= INITED_FLAG;
};

SvvInternalAction(SvvInternalSetNode, GetNodeForData, SvvInternalSetNode, SvvInternalObject Object)
{
	int comparation_result;
	while(SvvInternalSetNode_Inited(Receiver) && (comparation_result = SvvInternalObject_Compare(Object, Receiver->data) != 0))
	{
		if(comparation_result > 0)
		{
			Receiver = Receiver->right;
		} else {
			Receiver = Receiver->left;
		};
	};
	return Receiver;
};

SvvInternalAction(SvvInternalSetNode, Remove, void)
{
	while(1)
	{
		int children = (SvvInternalSetNode_Inited(Receiver->left) << 2) + SvvInternalSetNode_Inited(Receiver->right);
		SvvInternalSetNode node_to_delete;
		
		switch(children)
		{
			case 0:
				SvvInternalSetNode_DeInit(Receiver);
				SvvInternalSetNode_Destroy(Receiver->right);
				SvvInternalSetNode_Destroy(Receiver->left);
				return;
			case 1:
				node_to_delete = Receiver->right;
				SvvInternalSetNode_Destroy(Receiver->left);
				
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;
				
				Receiver->data = node_to_delete->data;
				SvvInternalSetNode_Destroy(node_to_delete);
				return;
			case 2:
				node_to_delete = Receiver->left;
				SvvInternalSetNode_Destroy(Receiver->right);
				
			Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;
				
				Receiver->data = node_to_delete->data;
				SvvInternalSetNode_Destroy(node_to_delete);
				return;
			case 3:
				node_to_delete = Receiver->left;
				while(SvvInternalSetNode_Inited(node_to_delete->right))
				{
					node_to_delete = node_to_delete->right;
				};
				Receiver->data = node_to_delete->data;
		};
	};
};

SvvInternalAction(SvvInternalSetNode, CleanSubTree, void)
{
	if(SvvInternalSetNode_Inited(Receiver))
	{
		SvvInternalSetNode_CleanSubTree(Receiver->left);
		SvvInternalSetNode_CleanSubTree(Receiver->right);
	};
	SvvInternalSetNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalSetNode, DeInit, void)
{
	Receiver->flags &= ~INITED_FLAG;
};

SvvInternalAction(SvvInternalSetNode, Inited, int)
{
	return (Receiver->flags & INITED_FLAG) != 0;
};

SvvInternalAction(SvvInternalSetNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalSetNode, GetData, SvvInternalObject)
{
	return Receiver->data;
};

