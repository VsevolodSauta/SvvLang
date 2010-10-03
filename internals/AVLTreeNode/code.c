#include "internals/basics.h"
#include "internals/AVLTreeNode/imports.h"


Object AVLTreeNode_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct AVLTreeNode));
	toReturn->gid =  3632466928133990400ull;
	Object_SetComparator(toReturn, &AVLTreeNode_Compare);
	Object_SetDestructor(toReturn, &AVLTreeNode_Destroy);
	Object_SetCloner(toReturn, &AVLTreeNode_Clone);
	((AVLTreeNode) (toReturn->entity))->_parent = _nil;
	((AVLTreeNode) (toReturn->entity))->_left = _nil;
	((AVLTreeNode) (toReturn->entity))->_right = _nil;
	((AVLTreeNode) (toReturn->entity))->_height = _nil;
	((AVLTreeNode) (toReturn->entity))->_data = _nil;
	toReturn = AVLTreeNode_Init(toReturn);
	return toReturn;
}

Object AVLTreeNode_Init(Object _self)
{
	(((AVLTreeNode) (_self->entity))->_height) = NumberFactory_FromLong(_numberFactory, -1);
	return _self;
}

Object AVLTreeNode_Destroy(Object _self)
{
	Object_Release((((AVLTreeNode) (_self->entity))->_data));
	Object_Release((((AVLTreeNode) (_self->entity))->_height));
	Object_Release((((AVLTreeNode) (_self->entity))->_left));
	Object_Release((((AVLTreeNode) (_self->entity))->_right));
	return Object_Destroy(_self);
}

Object AVLTreeNode_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = AVLTreeNode_Create();
	Object_SetRetaining(&(((AVLTreeNode) (_toReturn->entity))->_data), Object_Retain((((AVLTreeNode) (_self->entity))->_data)));
	Object_SetCloning(&(((AVLTreeNode) (_toReturn->entity))->_height), (((AVLTreeNode) (_self->entity))->_height));
	if((Logic_Not(AVLTreeNode_IsLeaf(_toReturn))) != _false)
	{
		AVLTreeNode_SetLeft(_toReturn, Object_TempClone((((AVLTreeNode) (_self->entity))->_left)));
		AVLTreeNode_SetRight(_toReturn, Object_TempClone((((AVLTreeNode) (_self->entity))->_right)));
	}
	return _toReturn;
}

Object AVLTreeNode_Compare(Object _self, Object _avlTreeNode)
{
	Object _candidate;
	_candidate = Object_Compare((((AVLTreeNode) (_self->entity))->_data), (((AVLTreeNode) (_avlTreeNode->entity))->_data));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		return _candidate;
	}
	_candidate = Object_Compare((((AVLTreeNode) (_self->entity))->_height), (((AVLTreeNode) (_avlTreeNode->entity))->_height));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		return _candidate;
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(Object_Hash((((AVLTreeNode) (_self->entity))->_right)), Object_Hash((((AVLTreeNode) (_avlTreeNode->entity))->_right))) == _equal)) != _false)
	{
		return Object_Compare(Object_Hash((((AVLTreeNode) (_self->entity))->_left)), Object_Hash((((AVLTreeNode) (_avlTreeNode->entity))->_left)));
	}
	else
	{
		return Object_Compare(Object_Hash((((AVLTreeNode) (_self->entity))->_right)), Object_Hash((((AVLTreeNode) (_avlTreeNode->entity))->_right)));
	}
}

Object AVLTreeNode_SetData(Object _self, Object _object)
{
	Object_SetRetaining(&(((AVLTreeNode) (_self->entity))->_data), _object);
	if((AVLTreeNode_IsLeaf(_self)) != _false)
	{
		Object_SetReleasing(&(((AVLTreeNode) (_self->entity))->_left), AVLTreeNode_Create());
		Object_SetReleasing(&(((AVLTreeNode) (_self->entity))->_right), AVLTreeNode_Create());
		(((AVLTreeNode) (_self->entity))->_height) = NumberFactory_FromLong(_numberFactory, 0);
	}
	return _self;
}

Object AVLTreeNode_CalculateHeightOnce(Object _self)
{
	(((AVLTreeNode) (_self->entity))->_height) = Number_Max(Number_Add((((AVLTreeNode) ((((AVLTreeNode) (_self->entity))->_left)->entity))->_height), NumberFactory_FromLong(_numberFactory, 1)), Number_Add((((AVLTreeNode) ((((AVLTreeNode) (_self->entity))->_right)->entity))->_height), NumberFactory_FromLong(_numberFactory, 1)));
	return _self;
}

Object AVLTreeNode_Balance(Object _self)
{
	if((AVLTreeNode_IsLeaf((((AVLTreeNode) (_self->entity))->_parent))) != _false)
	{
		return _self;
	}
	if((AVLTreeNode_IsLeaf((((AVLTreeNode) ((((AVLTreeNode) (_self->entity))->_parent)->entity))->_parent))) != _false)
	{
		return _self;
	}
	Object _pivot;
	_pivot = (((AVLTreeNode) ((((AVLTreeNode) (_self->entity))->_parent)->entity))->_parent);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(Number_Abs(Number_Sub((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_height))), NumberFactory_FromLong(_numberFactory, 2)) == _less)) != _false)
	{
		return _self;
	}
	Object _group1;
	_group1;
	Object _group2;
	_group2;
	Object _group3;
	_group3;
	Object _group4;
	_group4;
	Object _tempData;
	_tempData = Object_Retain((((AVLTreeNode) (_pivot->entity))->_data));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_height)) == _greater)) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_height)) == _greater)) != _false)
		{
			_group1 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_left);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_right);
			_group4 = (((AVLTreeNode) (_pivot->entity))->_right);
			Object_SetRetaining(&(((AVLTreeNode) (_pivot->entity))->_data), (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_data));
			Object_SetRetaining(&(((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_data), _tempData);
			AVLTreeNode_SetRight(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right));
		}
		else
		{
			_group1 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_right);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right);
			_group4 = (((AVLTreeNode) (_pivot->entity))->_right);
			Object_SetRetaining(&(((AVLTreeNode) (_pivot->entity))->_data), (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_data));
			Object_SetRetaining(&(((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_data), _tempData);
			AVLTreeNode_SetRight(_pivot, (((AVLTreeNode) (_pivot->entity))->_left));
			AVLTreeNode_SetLeft(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left));
		}
	}
	else
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_height)) == _greater)) != _false)
		{
			_group1 = (((AVLTreeNode) (_pivot->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right)->entity))->_left);
			_group4 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right)->entity))->_right);
			Object_SetRetaining(&(((AVLTreeNode) (_pivot->entity))->_data), (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_data));
			Object_SetRetaining(&(((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_data), _tempData);
			AVLTreeNode_SetLeft(_pivot, (((AVLTreeNode) (_pivot->entity))->_right));
			AVLTreeNode_SetRight(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right));
		}
		else
		{
			_group1 = (((AVLTreeNode) (_pivot->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_left);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_right);
			_group4 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right);
			Object_SetRetaining(&(((AVLTreeNode) (_pivot->entity))->_data), (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_data));
			Object_SetRetaining(&(((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_data), _tempData);
			AVLTreeNode_SetLeft(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left));
		}
	}
	AVLTreeNode_SetLeft((((AVLTreeNode) (_pivot->entity))->_left), _group1);
	AVLTreeNode_SetRight((((AVLTreeNode) (_pivot->entity))->_left), _group2);
	AVLTreeNode_SetLeft((((AVLTreeNode) (_pivot->entity))->_right), _group3);
	AVLTreeNode_SetRight((((AVLTreeNode) (_pivot->entity))->_right), _group4);
	AVLTreeNode_CalculateHeightOnce((((AVLTreeNode) (_pivot->entity))->_left));
	AVLTreeNode_CalculateHeightOnce((((AVLTreeNode) (_pivot->entity))->_right));
	AVLTreeNode_CalculateHeightOnce(_pivot);
	Object_Release(_tempData);
	return _self;
}

Object AVLTreeNode_SetLeft(Object _self, Object _node)
{
	Object_SetRetaining(&(((AVLTreeNode) (_self->entity))->_left), _node);
	(((AVLTreeNode) (_node->entity))->_parent) = _self;
	return _self;
}

Object AVLTreeNode_SetRight(Object _self, Object _node)
{
	Object_SetRetaining(&(((AVLTreeNode) (_self->entity))->_right), _node);
	(((AVLTreeNode) (_node->entity))->_parent) = _self;
	return _self;
}

Object AVLTreeNode_FindNodeForObject(Object _self, Object _object)
{
	Object _toReturn;
	_toReturn = _self;
	while((Logic_Not(AVLTreeNode_IsLeaf(_toReturn))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) (_toReturn->entity))->_data), _object) == _equal)) != _false)
		{
			return _toReturn;
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) (_toReturn->entity))->_data), _object) == _greater)) != _false)
		{
			_toReturn = (((AVLTreeNode) (_toReturn->entity))->_left);
		}
		else
		{
			_toReturn = (((AVLTreeNode) (_toReturn->entity))->_right);
		}
	}
	return _toReturn;
}

Object AVLTreeNode_IsLeaf(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) (_self->entity))->_height), NumberFactory_FromLong(_numberFactory, -1)) == _equal);
}

Object AVLTreeNode_DeleteFromTree(Object _self)
{
	Object _node;
	_node = _self;
	if((Logic_Not(AVLTreeNode_IsLeaf((((AVLTreeNode) (_node->entity))->_left)))) != _false)
	{
		_node = (((AVLTreeNode) (_node->entity))->_left);
		while((Logic_Not(AVLTreeNode_IsLeaf(_node))) != _false)
		{
			_node = (((AVLTreeNode) (_node->entity))->_right);
		}
		_node = (((AVLTreeNode) (_node->entity))->_parent);
		Object_Release((((AVLTreeNode) (_node->entity))->_right));
		AVLTreeNode_SetRight((((AVLTreeNode) (_node->entity))->_parent), (((AVLTreeNode) (_node->entity))->_left));
	}
	else if((Logic_Not(AVLTreeNode_IsLeaf((((AVLTreeNode) (_self->entity))->_right)))) != _false)
	{
		_node = (((AVLTreeNode) (_node->entity))->_right);
		while((Logic_Not(AVLTreeNode_IsLeaf(_node))) != _false)
		{
			_node = (((AVLTreeNode) (_node->entity))->_left);
		}
		_node = (((AVLTreeNode) (_node->entity))->_parent);
		Object_Release((((AVLTreeNode) (_node->entity))->_left));
		AVLTreeNode_SetLeft((((AVLTreeNode) (_node->entity))->_parent), (((AVLTreeNode) (_node->entity))->_right));
	}
	else
	{
		Object_Release((((AVLTreeNode) (_self->entity))->_left));
		Object_Release((((AVLTreeNode) (_self->entity))->_right));
		(((AVLTreeNode) (_self->entity))->_height) = NumberFactory_FromLong(_numberFactory, -1);
		AVLTreeNode_RebalanceToRoot(_self);
		return _self;
	}
	Object _nodeParent;
	_nodeParent = (((AVLTreeNode) (_node->entity))->_parent);
	Object _tempData;
	_tempData = Object_Retain((((AVLTreeNode) (_node->entity))->_data));
	Object_SetRetaining(&(((AVLTreeNode) (_node->entity))->_data), (((AVLTreeNode) (_self->entity))->_data));
	Object_SetRetaining(&(((AVLTreeNode) (_self->entity))->_data), _tempData);
	Object_Release(_tempData);
	Object_Release(_node);
	AVLTreeNode_RebalanceToRoot(_nodeParent);
	return _self;
}

Object AVLTreeNode_RebalanceToRoot(Object _self)
{
	Object _node;
	_node = _self;
	while((Logic_Not(AVLTreeNode_IsLeaf(_node))) != _false)
	{
		AVLTreeNode_CalculateHeightOnce(_node);
		AVLTreeNode_Balance(_node);
		_node = (((AVLTreeNode) (_node->entity))->_parent);
	}
	return _self;
}
