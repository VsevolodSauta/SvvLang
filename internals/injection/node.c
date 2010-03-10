#include "internals/basics.h"
#include "internals/injection/node.h"

#define INITED_FLAG 1

SvvInternalCreator(SvvInternalInjectionNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalInjectionNode)));
};

SvvInternalAction(SvvInternalInjectionNode, Init, void, SvvInternalObject Key, SvvInternalInjectionNode Value)
{
	Receiver->key = Key;
	Receiver->value = Value;
	Receiver->left = SvvInternalInjectionNode_Create();
	Receiver->right = SvvInternalInjectionNode_Create();
	SvvInternalInjectionNode_DeInit(Receiver->left);
	SvvInternalInjectionNode_DeInit(Receiver->right);
	Receiver->left->parent = Receiver->right->parent = Receiver;
	Receiver->flags |= INITED_FLAG;
};

SvvInternalAction(SvvInternalInjectionNode, GetNodeForKey, SvvInternalInjectionNode, SvvInternalObject Key)
{
	int comparation_result;
	while(SvvInternalInjectionNode_Inited(Receiver) && (comparation_result = SvvInternalObject_Compare(Key, Receiver->key) != 0))
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

SvvInternalAction(SvvInternalInjectionNode, Remove, void)
{
	while(1)
	{
		int children = (SvvInternalInjectionNode_Inited(Receiver->left) << 2) + SvvInternalInjectionNode_Inited(Receiver->right);
		SvvInternalInjectionNode node_to_delete;
	
		switch(children)
		{
			case 0:
				SvvInternalInjectionNode_DeInit(Receiver);
				SvvInternalInjectionNode_Destroy(Receiver->right);
				SvvInternalInjectionNode_Destroy(Receiver->left);
				return;
			case 1:
				node_to_delete = Receiver->right;
				SvvInternalInjectionNode_Destroy(Receiver->left);
			
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;


				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				Receiver->value->value = Receiver;
				SvvInternalInjectionNode_Destroy(node_to_delete);
				return;
			case 2:
				node_to_delete = Receiver->left;
				SvvInternalInjectionNode_Destroy(Receiver->right);
				
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				Receiver->value->value = Receiver;
				SvvInternalInjectionNode_Destroy(node_to_delete);
				return;
			case 3:
				node_to_delete = Receiver->left;
				while(SvvInternalInjectionNode_Inited(node_to_delete->right))
				{
					node_to_delete = node_to_delete->right;
				};

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				Receiver->value->value = Receiver;
				
				Receiver = node_to_delete;
		};
	};
};

SvvInternalAction(SvvInternalInjectionNode, CleanSubTree, void)
{
	if(SvvInternalInjectionNode_Inited(Receiver))
	{
		SvvInternalInjectionNode_CleanSubTree(Receiver->left);
		SvvInternalInjectionNode_CleanSubTree(Receiver->right);
	};
	SvvInternalInjectionNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalInjectionNode, DeInit, void)
{
	Receiver->flags &= ~INITED_FLAG;
};

SvvInternalAction(SvvInternalInjectionNode, Inited, int)
{
	return (Receiver->flags & INITED_FLAG) != 0;
};

SvvInternalAction(SvvInternalInjectionNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalInjectionNode, GetValue, SvvInternalInjectionNode)
{
	return Receiver->value;
};

SvvInternalAction(SvvInternalInjectionNode, SetValue, void, SvvInternalInjectionNode Value)
{
	Receiver->value = Value;
};

SvvInternalAction(SvvInternalInjectionNode, GetKey, SvvInternalObject)
{
	return Receiver->key;
};
