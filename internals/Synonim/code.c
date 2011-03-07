#include "internals/basics.h"
#include "internals/Synonim/imports.h"


Object Synonim_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Synonim: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Synonim));
	_self->gid =  6761424502691563520ull;
	Object_SetComparator(_self, &Synonim_Compare);
	Object_SetDestructor(_self, &Synonim_Destroy);
	Object_SetCloner(_self, &Synonim_Clone);
	Object_SetDeepCloner(_self, &Synonim_DeepClone);
	((Synonim) (_self->entity))->_uid = _nil;
	((Synonim) (_self->entity))->_references = _nil;
	_self = Synonim_Init(_self);
	DPOPS ("Synonim: Create ended.")
	return _self;
}

Object Synonim_Init(Object _self)
{
	DPUSHS ("Synonim: Init begined.")
	ASSERT_C ( "Synonim:Init --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	(((Synonim) (_self->entity))->_references) = List_Create();
	Object_Autorelease(_self);
	Object toReturn = _self;
	DPOPS ("Synonim: Init ended.")
	return toReturn;
}

Object Synonim_SetUID(Object _self, Object _uid)
{
	DPUSHS ("Synonim: SetUID begined.")
	ASSERT_C ( "Synonim:SetUID --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:SetUID --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object_SetRetaining(&(((Synonim) (_self->entity))->_uid), _uid);
	Object toReturn = _self;
	DPOPS ("Synonim: SetUID ended.")
	return toReturn;
}

Object Synonim_GetUID(Object _self)
{
	DPUSHS ("Synonim: GetUID begined.")
	ASSERT_C ( "Synonim:GetUID --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	Object toReturn = (((Synonim) (_self->entity))->_uid);
	DPOPS ("Synonim: GetUID ended.")
	return toReturn;
}

Object Synonim_Unite(Object _self, Object _synonim)
{
	DPUSHS ("Synonim: Unite begined.")
	ASSERT_C ( "Synonim:Unite --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:Unite --- Checking for correct parameter type failed at parameter _synonim.", _synonim->gid ==  6761424502691563520ull || _synonim == _nil )
	Object _iterator;
	_iterator = List_First((((Synonim) (_synonim->entity))->_references));
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		Object _reference;
		_reference = Object_Retain(ListIterator_ListMapData(_iterator));
		ListIterator_ThisRemove(_iterator);
		Synonim_AddReference(_self, _reference);
		Object_Release(_reference);
	}
	Object toReturn = _self;
	DPOPS ("Synonim: Unite ended.")
	return toReturn;
}

Object Synonim_AddToNamespaceWithName(Object _self, Object _namespace, Object _name)
{
	DPUSHS ("Synonim: AddToNamespaceWithName begined.")
	ASSERT_C ( "Synonim:AddToNamespaceWithName --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:AddToNamespaceWithName --- Checking for correct parameter type failed at parameter _namespace.", _namespace->gid ==  2108332898258556672ull || _namespace == _nil )
	ASSERT_C ( "Synonim:AddToNamespaceWithName --- Checking for correct parameter type failed at parameter _name.", _name->gid ==  3732711262168886272ull || _name == _nil )
	Object _reference;
	_reference = ListMap_Create();
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), _namespace);
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _name);
	List_PushSorted((((Synonim) (_self->entity))->_references), _reference);
	Object_Release(_reference);
	ListMap_Add(_namespace, _name, _self);
	Object toReturn = _self;
	DPOPS ("Synonim: AddToNamespaceWithName ended.")
	return toReturn;
}

Object Synonim_AddReference(Object _self, Object _location)
{
	DPUSHS ("Synonim: AddReference begined.")
	ASSERT_C ( "Synonim:AddReference --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:AddReference --- Checking for correct parameter type failed at parameter _location.", _location->gid ==  2108332898258556672ull || _location == _nil )
	List_PushSorted((((Synonim) (_self->entity))->_references), _location);
	ListMap_Add(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), _self);
	Object toReturn = _self;
	DPOPS ("Synonim: AddReference ended.")
	return toReturn;
}

Object Synonim_RemoveReference(Object _self, Object _location)
{
	DPUSHS ("Synonim: RemoveReference begined.")
	ASSERT_C ( "Synonim:RemoveReference --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:RemoveReference --- Checking for correct parameter type failed at parameter _location.", _location->gid ==  2108332898258556672ull || _location == _nil )
	if((List_RemoveFirstWithConfirmation((((Synonim) (_self->entity))->_references), _location)) != _false)
	{
		ListMap_Remove(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
	}
	Object toReturn = _self;
	DPOPS ("Synonim: RemoveReference ended.")
	return toReturn;
}

Object Synonim_RemoveNamespace(Object _self, Object _namespace)
{
	DPUSHS ("Synonim: RemoveNamespace begined.")
	ASSERT_C ( "Synonim:RemoveNamespace --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:RemoveNamespace --- Checking for correct parameter type failed at parameter _namespace.", _namespace->gid ==  2108332898258556672ull || _namespace == _nil )
	Object _iterator;
	_iterator = List_First((((Synonim) (_self->entity))->_references));
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(ListIterator_ListMapData(_iterator), StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), _namespace) == _equal)) != _false)
		{
			ListIterator_ThisRemove(_iterator);
		}
		else
		{
			ListIterator_Next(_iterator);
		}
	}
	Object toReturn = _self;
	DPOPS ("Synonim: RemoveNamespace ended.")
	return toReturn;
}

Object Synonim_Destroy(Object _self)
{
	DPUSHS ("Synonim: Destroy begined.")
	ASSERT_C ( "Synonim:Destroy --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	Object_Release((((Synonim) (_self->entity))->_uid));
	Object_Release((((Synonim) (_self->entity))->_references));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Synonim: Destroy ended.")
	return toReturn;
}

Object Synonim_Clone(Object _self)
{
	DPUSHS ("Synonim: Clone begined.")
	ASSERT_C ( "Synonim:Clone --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	Object _toReturn;
	_toReturn = Synonim_Create();
	Object_SetRetaining(&(((Synonim) (_toReturn->entity))->_uid), (((Synonim) (_self->entity))->_uid));
	Object toReturn = _self;
	DPOPS ("Synonim: Clone ended.")
	return toReturn;
}

Object Synonim_DeepClone(Object _self)
{
	DPUSHS ("Synonim: DeepClone begined.")
	ASSERT_C ( "Synonim:DeepClone --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	Object _toReturn;
	_toReturn = Synonim_Create();
	Object_SetRetaining(&(((Synonim) (_toReturn->entity))->_uid), (((Synonim) (_self->entity))->_uid));
	Object toReturn = _self;
	DPOPS ("Synonim: DeepClone ended.")
	return toReturn;
}

Object Synonim_Compare(Object _self, Object _synonim)
{
	DPUSHS ("Synonim: Compare begined.")
	ASSERT_C ( "Synonim:Compare --- Checking for correct object type failed.", _self->gid ==  6761424502691563520ull )
	ASSERT_C ( "Synonim:Compare --- Checking for correct parameter type failed at parameter _synonim.", _synonim->gid ==  6761424502691563520ull || _synonim == _nil )
	Object toReturn = Object_Compare((((Synonim) (_self->entity))->_uid), (((Synonim) (_synonim->entity))->_uid));
	DPOPS ("Synonim: Compare ended.")
	return toReturn;
}
