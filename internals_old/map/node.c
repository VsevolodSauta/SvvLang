#include "internals/basics.h"
#include "internals/map/node.h"

#define INITED_FLAG 1

SvvInternalCreator(SvvInternalMapNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMapNode)));
};

SvvInternalAction(SvvInternalMapNode, Init, void, SvvInternalObject Key, SvvInternalObject Value)
{
	Receiver->key = Key;
	Receiver->value = Value;
	Receiver->left = SvvInternalMapNode_Create();
	Receiver->right = SvvInternalMapNode_Create();
	SvvInternalMapNode_DeInit(Receiver->left);
	SvvInternalMapNode_DeInit(Receiver->right);
	Receiver->left->parent = Receiver->right->parent = Receiver;
	Receiver->flags |= INITED_FLAG;
};

SvvInternalAction(SvvInternalMapNode, GetNodeForKey, SvvInternalMapNode, SvvInternalObject Key)
{
	int comparation_result;
	while(SvvInternalMapNode_Inited(Receiver) && 
		(comparation_result = SvvInternalObject_Compare(Key, Receiver->key) != 0))
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

SvvInternalAction(SvvInternalMapNode, Remove, void)
{
	while(1)
	{
		int children = (SvvInternalMapNode_Inited(Receiver->left) << 2) + SvvInternalMapNode_Inited(Receiver->right);
		SvvInternalMapNode node_to_delete;

		switch(children)
		{
			case 0:
				SvvInternalMapNode_DeInit(Receiver);
				SvvInternalMapNode_Destroy(Receiver->right);
				SvvInternalMapNode_Destroy(Receiver->left);
				return;
			case 1:
				node_to_delete = Receiver->right;
				SvvInternalMapNode_Destroy(Receiver->left);
			
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;


				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				SvvInternalMapNode_Destroy(node_to_delete);
				return;
			case 2:
				node_to_delete = Receiver->left;
				SvvInternalMapNode_Destroy(Receiver->right);
				
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				SvvInternalMapNode_Destroy(node_to_delete);
				return;
			case 3:
				node_to_delete = Receiver->left;
				while(SvvInternalMapNode_Inited(node_to_delete->right))
				{
					node_to_delete = node_to_delete->right;
				};

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
		};
		Receiver = node_to_delete;
	};
};

SvvInternalAction(SvvInternalMapNode, CleanSubTree, void)
{
	if(SvvInternalMapNode_Inited(Receiver))
	{
		SvvInternalMapNode_CleanSubTree(Receiver->left);
		SvvInternalMapNode_CleanSubTree(Receiver->right);
	};
	SvvInternalMapNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalMapNode, DeInit, void)
{
	Receiver->flags &= ~INITED_FLAG;
};

SvvInternalAction(SvvInternalMapNode, Inited, int)
{
	return (Receiver->flags & INITED_FLAG) != 0;
};

SvvInternalAction(SvvInternalMapNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalMapNode, GetValue, SvvInternalObject)
{
	return Receiver->value;
};

SvvInternalAction(SvvInternalMapNode, SetValue, void, SvvInternalObject Object)
{
	Receiver->value = Object;
};

SvvInternalAction(SvvInternalMapNode, GetKey, SvvInternalObject)
{
	return Receiver->key;
};

