#include "internals/basics.h"
#include "internals/Synonim/imports.h"


Object Synonim_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Synonim));
	toReturn->gid =  6761424502691563520ull;
	Object_SetComparator(toReturn, &Synonim_Compare);
	Object_SetDestructor(toReturn, &Synonim_Destroy);
	Object_SetCloner(toReturn, &Synonim_Clone);
	((Synonim) (toReturn->entity))->_object = _nil;
	((Synonim) (toReturn->entity))->_references = _nil;
	toReturn = Synonim_Init(toReturn);
	return toReturn;
}

Object Synonim_Init(Object _self)
{
	Object _references;
	_references = List_Create();
	return _self;
}

Object Synonim_SetObject(Object _self, Object _object)
{
	Object_SetRetaining(&(((Synonim) (_self->entity))->_object), _object);
	return _self;
}

Object Synonim_Unite(Object _self, Object _synonim)
{
	Object _iterator;
	_iterator = List_First((((Synonim) (_self->entity))->_references));
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		Synonim_AddReference(_synonim, ListIterator_ListMapData(_iterator));
		ListIterator_ThisRemove(_iterator);
		Object_Release(_self);
		ListIterator_Next(_iterator);
	}
	return _nil;
}

Object Synonim_AddReference(Object _self, Object _location)
{
	List_PushSorted((((Synonim) (_self->entity))->_references), _location);
	ListMap_Add(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), _self);
	Object_Retain(_self);
	return _self;
}

Object Synonim_RemoveReference(Object _self, Object _location)
{
	if((List_RemoveFirstWithConfirmation((((Synonim) (_self->entity))->_references), _location)) != _false)
	{
		ListMap_Remove(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Object_Release(_self);
	}
	return _self;
}

Object Synonim_RemoveNamespace(Object _self, Object _namespace)
{
	Object _iterator;
	_iterator = List_First((((Synonim) (_self->entity))->_references));
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(ListIterator_ListMapData(_iterator), StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), _namespace) == _equal)) != _false)
		{
			ListIterator_ThisRemove(_iterator);
			Object_Release(_self);
		}
		else
		{
			ListIterator_Next(_iterator);
		}
	}
	return _self;
}

Object Synonim_Destroy(Object _self)
{
	Object_Release((((Synonim) (_self->entity))->_object));
	Object_Release((((Synonim) (_self->entity))->_references));
	return Object_Destroy(_self);
}

Object Synonim_Clone(Object _self)
{
	return _self;
}

Object Synonim_Compare(Object _self, Object _synonim)
{
	return Object_Compare((((Synonim) (_self->entity))->_object), (((Synonim) (_synonim->entity))->_object));
}
