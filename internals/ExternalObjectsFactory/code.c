#include "internals/basics.h"
#include "internals/ExternalObjectsFactory/imports.h"


Object ExternalObjectsFactory_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalObjectsFactory: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalObjectsFactory));
	_self->gid =  8994984795938592768ull;
	Object_SetComparator(_self, &ExternalObjectsFactory_Compare);
	Object_SetDestructor(_self, &ExternalObjectsFactory_Destroy);
	Object_SetCloner(_self, &ExternalObjectsFactory_Clone);
	Object_SetDeepCloner(_self, &ExternalObjectsFactory_DeepClone);
	((ExternalObjectsFactory) (_self->entity))->_machine = _nil;
	_self = ExternalObjectsFactory_Init(_self);
	DPOPS ("ExternalObjectsFactory: Create ended.")
	return _self;
}

Object ExternalObjectsFactory_Init(Object _self)
{
	DPUSHS ("ExternalObjectsFactory: Init begined.")
	ASSERT_C ( "ExternalObjectsFactory:Init --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	Object toReturn = _self;
	DPOPS ("ExternalObjectsFactory: Init ended.")
	return toReturn;
}

Object ExternalObjectsFactory_Destroy(Object _self)
{
	DPUSHS ("ExternalObjectsFactory: Destroy begined.")
	ASSERT_C ( "ExternalObjectsFactory:Destroy --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	Object_Release((((ExternalObjectsFactory) (_self->entity))->_machine));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalObjectsFactory: Destroy ended.")
	return toReturn;
}

Object ExternalObjectsFactory_Compare(Object _self, Object _eof)
{
	DPUSHS ("ExternalObjectsFactory: Compare begined.")
	ASSERT_C ( "ExternalObjectsFactory:Compare --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	Object toReturn = _equal;
	DPOPS ("ExternalObjectsFactory: Compare ended.")
	return toReturn;
}

Object ExternalObjectsFactory_Clone(Object _self)
{
	DPUSHS ("ExternalObjectsFactory: Clone begined.")
	ASSERT_C ( "ExternalObjectsFactory:Clone --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalObjectsFactory: Clone ended.")
	return toReturn;
}

Object ExternalObjectsFactory_DeepClone(Object _self)
{
	DPUSHS ("ExternalObjectsFactory: DeepClone begined.")
	ASSERT_C ( "ExternalObjectsFactory:DeepClone --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalObjectsFactory: DeepClone ended.")
	return toReturn;
}

Object ExternalObjectsFactory_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalObjectsFactory: SetMachine begined.")
	ASSERT_C ( "ExternalObjectsFactory:SetMachine --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	ASSERT_C ( "ExternalObjectsFactory:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalObjectsFactory) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalObjectsFactory: SetMachine ended.")
	return toReturn;
}

Object ExternalObjectsFactory_CreateValue(Object _self, Object _value)
{
	DPUSHS ("ExternalObjectsFactory: CreateValue begined.")
	ASSERT_C ( "ExternalObjectsFactory:CreateValue --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	if((LogicFactory_FromLong(_logicFactory, _value->gid == 15425740279749906432ull)) != _false)
	{
		Object toReturn = ExternalObjectsFactory_CreateNumber(_self, _value);
		DPOPS ("ExternalObjectsFactory: CreateValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, _value->gid ==  3732711262168886272ull)) != _false)
	{
		Object toReturn = ExternalObjectsFactory_CreateList(_self, _value);
		DPOPS ("ExternalObjectsFactory: CreateValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, _value->gid ==  2108332898258556672ull)) != _false)
	{
		Object toReturn = ExternalObjectsFactory_CreateListMap(_self, _value);
		DPOPS ("ExternalObjectsFactory: CreateValue ended.")
		return toReturn;
	}
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Попытка создания объекта неивестного типа.", 79));
	Object toReturn = _nil;
	DPOPS ("ExternalObjectsFactory: CreateValue ended.")
	return toReturn;
}

Object ExternalObjectsFactory_CreateNumber(Object _self, Object _number)
{
	DPUSHS ("ExternalObjectsFactory: CreateNumber begined.")
	ASSERT_C ( "ExternalObjectsFactory:CreateNumber --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	ASSERT_C ( "ExternalObjectsFactory:CreateNumber --- Checking for correct parameter type failed at parameter _number.", _number->gid == 15425740279749906432ull || _number == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _toReturn;
	_toReturn = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_object), _uid);
	ListMap_ObjectSetProperty(Machine_UIDToObject((((ExternalObjectsFactory) (_self->entity))->_machine), _toReturn), _number, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object toReturn = _toReturn;
	DPOPS ("ExternalObjectsFactory: CreateNumber ended.")
	return toReturn;
}

Object ExternalObjectsFactory_CreateString(Object _self, Object _string)
{
	DPUSHS ("ExternalObjectsFactory: CreateString begined.")
	ASSERT_C ( "ExternalObjectsFactory:CreateString --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	ASSERT_C ( "ExternalObjectsFactory:CreateString --- Checking for correct parameter type failed at parameter _string.", _string->gid ==  3732711262168886272ull || _string == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Строка", 12));
	Object _toReturn;
	_toReturn = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_object), _uid);
	ListMap_ObjectSetProperty(Machine_UIDToObject((((ExternalObjectsFactory) (_self->entity))->_machine), _toReturn), _string, StringFactory_FromUTF8(_stringFactory, "Строка", 12));
	Object toReturn = _toReturn;
	DPOPS ("ExternalObjectsFactory: CreateString ended.")
	return toReturn;
}

Object ExternalObjectsFactory_CreateList(Object _self, Object _list)
{
	DPUSHS ("ExternalObjectsFactory: CreateList begined.")
	ASSERT_C ( "ExternalObjectsFactory:CreateList --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	ASSERT_C ( "ExternalObjectsFactory:CreateList --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Object _toReturn;
	_toReturn = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_object), _uid);
	ListMap_ObjectSetProperty(Machine_UIDToObject((((ExternalObjectsFactory) (_self->entity))->_machine), _toReturn), _list, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	ListMap_ObjectSetProperty(Machine_UIDToObject((((ExternalObjectsFactory) (_self->entity))->_machine), _toReturn), ExternalEntitiesFactory_CreateEmptyList(_entitiesFactory), StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object toReturn = _toReturn;
	DPOPS ("ExternalObjectsFactory: CreateList ended.")
	return toReturn;
}

Object ExternalObjectsFactory_CreateListMap(Object _self, Object _listMap)
{
	DPUSHS ("ExternalObjectsFactory: CreateListMap begined.")
	ASSERT_C ( "ExternalObjectsFactory:CreateListMap --- Checking for correct object type failed.", _self->gid ==  8994984795938592768ull )
	ASSERT_C ( "ExternalObjectsFactory:CreateListMap --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Строковое отображение", 41));
	Object _toReturn;
	_toReturn = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalObjectsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_object), _uid);
	ListMap_ObjectSetProperty(Machine_UIDToObject((((ExternalObjectsFactory) (_self->entity))->_machine), _toReturn), _listMap, StringFactory_FromUTF8(_stringFactory, "Строковое отображение", 41));
	Object toReturn = _toReturn;
	DPOPS ("ExternalObjectsFactory: CreateListMap ended.")
	return toReturn;
}
