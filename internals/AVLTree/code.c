#include "internals/basics.h"
#include "internals/AVLTree/imports.h"


Object AVLTree_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct AVLTree));
	toReturn->gid =  7095926952188348416ull;
	Object_SetComparator(toReturn, &AVLTree_Compare);
	Object_SetDestructor(toReturn, &AVLTree_Destroy);
	Object_SetCloner(toReturn, &AVLTree_Clone);
	((AVLTree) (toReturn->entity))->_root = _nil;
	toReturn = AVLTree_Init(toReturn);
	return toReturn;
}

Object AVLTree_Init(Object _self)
{
	(((AVLTree) (_self->entity))->_root) = AVLTreeNode_SetData(AVLTreeNode_Create(), _nil);
	(((AVLTreeNode) ((((AVLTree) (_self->entity))->_root)->entity))->_height) = NumberFactory_FromLong(_numberFactory, -1);
	return _self;
}

Object AVLTree_Destroy(Object _self)
{
	Object_Release((((AVLTree) (_self->entity))->_root));
	return Object_Release(_self);
}

Object AVLTree_Compare(Object _self, Object _avlTree)
{
	return Object_Compare((((AVLTree) (_self->entity))->_root), (((AVLTree) (_avlTree->entity))->_root));
}

Object AVLTree_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = AVLTree_Create();
	if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTree) (_toReturn->entity))->_root), _nil) != _equal)) != _false)
	{
		(((AVLTree) (_toReturn->entity))->_root) = Object_Clone((((AVLTree) (_self->entity))->_root));
	}
	return _toReturn;
}

Object AVLTree_Add(Object _self, Object _object)
{
	Object _node;
	_node = AVLTreeNode_FindNodeForObject((((AVLTreeNode) ((((AVLTree) (_self->entity))->_root)->entity))->_left), _object);
	if((AVLTreeNode_IsLeaf(_node)) != _false)
	{
		AVLTreeNode_SetData(_node, _object);
		AVLTreeNode_Balance(_node);
	}
	return _self;
}

Object AVLTree_Remove(Object _self, Object _object)
{
	Object _node;
	_node = AVLTreeNode_FindNodeForObject((((AVLTreeNode) ((((AVLTree) (_self->entity))->_root)->entity))->_left), _object);
	if((Logic_Not(AVLTreeNode_IsLeaf(_node))) != _false)
	{
		AVLTreeNode_DeleteFromTree(_node);
	}
	return _self;
}

Object AVLTree_AddWithComfirmation(Object _self)
{
	Object _node;
	Object _object;
	_node = AVLTreeNode_FindNodeForObject((((AVLTreeNode) ((((AVLTree) (_self->entity))->_root)->entity))->_left), _object);
	if((AVLTreeNode_IsLeaf(_node)) != _false)
	{
		AVLTreeNode_SetData(_node, _object);
		AVLTreeNode_Balance(_node);
		return _true;
	}
	else
	{
		return _false;
	}
}

Object AVLTree_RemoveWithConfirmation(Object _self, Object _object)
{
	Object _node;
	_node = AVLTreeNode_FindNodeForObject((((AVLTreeNode) ((((AVLTree) (_self->entity))->_root)->entity))->_left), _object);
	if((Logic_Not(AVLTreeNode_IsLeaf(_node))) != _false)
	{
		AVLTreeNode_DeleteFromTree(_node);
		return _true;
	}
	return _false;
}
