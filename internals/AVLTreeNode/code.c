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
	toReturn = AVLTreeNode_Init(toReturn);
	return toReturn;
}

Object AVLTreeNode_Init(Object _self)
{
	(((AVLTreeNode) (_self->entity))->_left) = _nil;
	(((AVLTreeNode) (_self->entity))->_right) = _nil;
	(((AVLTreeNode) (_self->entity))->_height) = Object_Retain(NumberFactory_FromLong(_numberFactory, -1));
	(((AVLTreeNode) (_self->entity))->_data) = _nil;
	(((AVLTreeNode) (_self->entity))->_parent) = _nil;
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
	(((AVLTreeNode) (_toReturn->entity))->_data) = Object_Retain((((AVLTreeNode) (_self->entity))->_data));
	(((AVLTreeNode) (_toReturn->entity))->_height) = Object_Clone((((AVLTreeNode) (_self->entity))->_height));
	if((Logic_Not(AVLTreeNode_IsLeaf(_toReturn))) != _false)
	{
		(((AVLTreeNode) (_toReturn->entity))->_left) = Object_Clone((((AVLTreeNode) (_self->entity))->_left));
		(((AVLTreeNode) ((((AVLTreeNode) (_toReturn->entity))->_left)->entity))->_parent) = _toReturn;
		(((AVLTreeNode) (_toReturn->entity))->_right) = Object_Clone((((AVLTreeNode) (_self->entity))->_left));
		(((AVLTreeNode) ((((AVLTreeNode) (_toReturn->entity))->_right)->entity))->_parent) = _toReturn;
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
	_candidate = Object_Compare((((AVLTreeNode) (_self->entity))->_height), (((AVLTreeNode) (_avlTreeNode->entity))->_data));
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
	Object _toRelease;
	_toRelease = (((AVLTreeNode) (_self->entity))->_data);
	(((AVLTreeNode) (_self->entity))->_data) = Object_Retain(_object);
	if((AVLTreeNode_IsLeaf(_self)) != _false)
	{
		(((AVLTreeNode) (_self->entity))->_left) = AVLTreeNode_Create();
		(((AVLTreeNode) (_self->entity))->_right) = AVLTreeNode_Create();
		(((AVLTreeNode) (_self->entity))->_height) = NumberFactory_FromLong(_numberFactory, 0);
	}
	else
	{
		Object_Release(_toRelease);
	}
	return _self;
}

Object AVLTreeNode_CalculateHeight(Object _self)
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
	if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_height)) == _greater)) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare((((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_height), (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_height)) == _greater)) != _false)
		{
			_group1 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_left);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_right);
			_group4 = (((AVLTreeNode) (_pivot->entity))->_right);
			Object _tempData;
			_tempData = (((AVLTreeNode) (_pivot->entity))->_data);
			(((AVLTreeNode) (_pivot->entity))->_data) = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_data);
			(((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right)->entity))->_data) = _tempData;
			AVLTreeNode_SetRight(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right));
		}
		else
		{
			_group1 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_left)->entity))->_right);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_right);
			_group4 = (((AVLTreeNode) (_pivot->entity))->_right);
			Object _tempData;
			_tempData = (((AVLTreeNode) (_pivot->entity))->_data);
			(((AVLTreeNode) (_pivot->entity))->_data) = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_data);
			(((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_left)->entity))->_data) = _tempData;
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
			Object _tempData;
			_tempData = (((AVLTreeNode) (_pivot->entity))->_data);
			(((AVLTreeNode) (_pivot->entity))->_data) = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_data);
			(((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_data) = _tempData;
			AVLTreeNode_SetLeft(_pivot, (((AVLTreeNode) (_pivot->entity))->_right));
			AVLTreeNode_SetRight(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right));
		}
		else
		{
			_group1 = (((AVLTreeNode) (_pivot->entity))->_left);
			_group2 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_left);
			_group3 = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_right);
			_group4 = (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_right);
			Object _tempData;
			_tempData = (((AVLTreeNode) (_pivot->entity))->_data);
			(((AVLTreeNode) (_pivot->entity))->_data) = (((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_data);
			(((AVLTreeNode) ((((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left)->entity))->_data) = _tempData;
			AVLTreeNode_SetLeft(_pivot, (((AVLTreeNode) ((((AVLTreeNode) (_pivot->entity))->_right)->entity))->_left));
		}
	}
	AVLTreeNode_SetLeft((((AVLTreeNode) (_pivot->entity))->_left), _group1);
	AVLTreeNode_SetRight((((AVLTreeNode) (_pivot->entity))->_left), _group2);
	AVLTreeNode_SetLeft((((AVLTreeNode) (_pivot->entity))->_right), _group3);
	AVLTreeNode_SetRight((((AVLTreeNode) (_pivot->entity))->_right), _group4);
	return _self;
}

Object AVLTreeNode_SetLeft(Object _self, Object _node)
{
	(((AVLTreeNode) (_self->entity))->_left) = _node;
	(((AVLTreeNode) (_node->entity))->_parent) = _self;
	return _self;
}

Object AVLTreeNode_SetRight(Object _self, Object _node)
{
	(((AVLTreeNode) (_self->entity))->_right) = _node;
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
