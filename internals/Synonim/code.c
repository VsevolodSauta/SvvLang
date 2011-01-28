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
	((Synonim) (_self->entity))->_object = _nil;
	((Synonim) (_self->entity))->_references = _nil;
	_self = Synonim_Init(_self);
	DPOPS ("Synonim: Create ended.")
	return _self;
}

Object Synonim_Init(Object _self)
{
	DPUSHS ("Synonim: Init begined.")
	Object _references;
	_references = List_Create();
	Object toReturn = _self;
	DPOPS ("Synonim: Init ended.")
	return toReturn;
}

Object Synonim_SetObject(Object _self, Object _object)
{
	DPUSHS ("Synonim: SetObject begined.")
	Object_SetRetaining(&(((Synonim) (_self->entity))->_object), _object);
	Object toReturn = _self;
	DPOPS ("Synonim: SetObject ended.")
	return toReturn;
}

Object Synonim_Object(Object _self)
{
	DPUSHS ("Synonim: Object begined.")
	Object toReturn = (((Synonim) (_self->entity))->_object);
	DPOPS ("Synonim: Object ended.")
	return toReturn;
}

Object Synonim_Unite(Object _self, Object _synonim)
{
	DPUSHS ("Synonim: Unite begined.")
	Object _iterator;
	_iterator = List_First((((Synonim) (_self->entity))->_references));
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		Synonim_AddReference(_synonim, ListIterator_ListMapData(_iterator));
		ListIterator_ThisRemove(_iterator);
		Object_Release(_self);
		ListIterator_Next(_iterator);
	}
	Object toReturn = _nil;
	DPOPS ("Synonim: Unite ended.")
	return toReturn;
}

Object Synonim_AddReference(Object _self, Object _location)
{
	DPUSHS ("Synonim: AddReference begined.")
	List_PushSorted((((Synonim) (_self->entity))->_references), _location);
	ListMap_Add(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), _self);
	Object_Retain(_self);
	Object toReturn = _self;
	DPOPS ("Synonim: AddReference ended.")
	return toReturn;
}

Object Synonim_RemoveReference(Object _self, Object _location)
{
	DPUSHS ("Synonim: RemoveReference begined.")
	if((List_RemoveFirstWithConfirmation((((Synonim) (_self->entity))->_references), _location)) != _false)
	{
		ListMap_Remove(ListMap_ListMapAt(_location, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33)), ListMap_ListAt(_location, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Object_Release(_self);
	}
	Object toReturn = _self;
	DPOPS ("Synonim: RemoveReference ended.")
	return toReturn;
}

Object Synonim_RemoveNamespace(Object _self, Object _namespace)
{
	DPUSHS ("Synonim: RemoveNamespace begined.")
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
	Object toReturn = _self;
	DPOPS ("Synonim: RemoveNamespace ended.")
	return toReturn;
}

Object Synonim_Destroy(Object _self)
{
	DPUSHS ("Synonim: Destroy begined.")
	Object_Release((((Synonim) (_self->entity))->_object));
	Object_Release((((Synonim) (_self->entity))->_references));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Synonim: Destroy ended.")
	return toReturn;
}

Object Synonim_Clone(Object _self)
{
	DPUSHS ("Synonim: Clone begined.")
	Object toReturn = _self;
	DPOPS ("Synonim: Clone ended.")
	return toReturn;
}

Object Synonim_DeepClone(Object _self)
{
	DPUSHS ("Synonim: DeepClone begined.")
	Object toReturn = _self;
	DPOPS ("Synonim: DeepClone ended.")
	return toReturn;
}

Object Synonim_Compare(Object _self, Object _synonim)
{
	DPUSHS ("Synonim: Compare begined.")
	Object toReturn = Object_Compare((((Synonim) (_self->entity))->_object), (((Synonim) (_synonim->entity))->_object));
	DPOPS ("Synonim: Compare ended.")
	return toReturn;
}
