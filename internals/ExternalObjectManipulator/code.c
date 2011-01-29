#include "internals/basics.h"
#include "internals/ExternalObjectManipulator/imports.h"


Object ExternalObjectManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalObjectManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalObjectManipulator));
	_self->gid =  8518571086308177920ull;
	Object_SetComparator(_self, &ExternalObjectManipulator_Compare);
	Object_SetDestructor(_self, &ExternalObjectManipulator_Destroy);
	Object_SetCloner(_self, &ExternalObjectManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalObjectManipulator_DeepClone);
	((ExternalObjectManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalObjectManipulator_Init(_self);
	DPOPS ("ExternalObjectManipulator: Create ended.")
	return _self;
}

Object ExternalObjectManipulator_Init(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Init begined.")
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Init ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Clone begined.")
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Clone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Destroy begined.")
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalObjectManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalObjectManipulator: Compare begined.")
	Object toReturn = _equal;
	DPOPS ("ExternalObjectManipulator: Compare ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalObjectManipulator: SetMachine begined.")
	(((ExternalObjectManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CreateUID(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: CreateUID begined.")
	AutoreleasePool_PushFrame(_autoreleasePool);
	Machine_LoadUIDWithNameToNamespace((((ExternalObjectManipulator) (_self->entity))->_machine), StringFactory_FromUTF8(_stringFactory, "Объект", 12), (((Machine) ((((ExternalObjectManipulator) (_self->entity))->_machine)->entity))->_globalContext));
	AutoreleasePool_PopFrame(_autoreleasePool);
		Object _uid;
Object toReturn = _uid;
	DPOPS ("ExternalObjectManipulator: CreateUID ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CloneUID(Object _self, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: CloneUID begined.")
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GenerateUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	Object _objectToReturn;
	_objectToReturn = Object_DeepClone(_object);
	Machine_SetUIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uidToReturn, _objectToReturn);
	Object_Release(_objectToReturn);
	Object toReturn = _uidToReturn;
	DPOPS ("ExternalObjectManipulator: CloneUID ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetBasicMethodWithNameForUID(Object _self, Object _method, Object _name, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: SetBasicMethodWithNameForUID begined.")
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый метод", 25), _method);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _true);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetBasicMethodWithNameForUID ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMethodWithNameForUID(Object _self, Object _methodBody, Object _name, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: SetMethodWithNameForUID begined.")
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8), _methodBody);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMethodWithNameForUID ended.")
	return toReturn;
}
