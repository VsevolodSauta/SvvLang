#include "internals/basics.h"
#include "internals/ExternalActorsFactory/imports.h"


Object ExternalActorsFactory_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalActorsFactory: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalActorsFactory));
	_self->gid =  8965844543623282688ull;
	Object_SetComparator(_self, &ExternalActorsFactory_Compare);
	Object_SetDestructor(_self, &ExternalActorsFactory_Destroy);
	Object_SetCloner(_self, &ExternalActorsFactory_Clone);
	Object_SetDeepCloner(_self, &ExternalActorsFactory_DeepClone);
	((ExternalActorsFactory) (_self->entity))->_machine = _nil;
	_self = ExternalActorsFactory_Init(_self);
	DPOPS ("ExternalActorsFactory: Create ended.")
	return _self;
}

Object ExternalActorsFactory_Init(Object _self)
{
	DPUSHS ("ExternalActorsFactory: Init begined.")
	ASSERT_C ( "ExternalActorsFactory:Init --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	Object toReturn = _self;
	DPOPS ("ExternalActorsFactory: Init ended.")
	return toReturn;
}

Object ExternalActorsFactory_Destroy(Object _self)
{
	DPUSHS ("ExternalActorsFactory: Destroy begined.")
	ASSERT_C ( "ExternalActorsFactory:Destroy --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	Object_Release((((ExternalActorsFactory) (_self->entity))->_machine));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalActorsFactory: Destroy ended.")
	return toReturn;
}

Object ExternalActorsFactory_Compare(Object _self, Object _eof)
{
	DPUSHS ("ExternalActorsFactory: Compare begined.")
	ASSERT_C ( "ExternalActorsFactory:Compare --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	Object toReturn = _equal;
	DPOPS ("ExternalActorsFactory: Compare ended.")
	return toReturn;
}

Object ExternalActorsFactory_Clone(Object _self)
{
	DPUSHS ("ExternalActorsFactory: Clone begined.")
	ASSERT_C ( "ExternalActorsFactory:Clone --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalActorsFactory: Clone ended.")
	return toReturn;
}

Object ExternalActorsFactory_DeepClone(Object _self)
{
	DPUSHS ("ExternalActorsFactory: DeepClone begined.")
	ASSERT_C ( "ExternalActorsFactory:DeepClone --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalActorsFactory: DeepClone ended.")
	return toReturn;
}

Object ExternalActorsFactory_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalActorsFactory: SetMachine begined.")
	ASSERT_C ( "ExternalActorsFactory:SetMachine --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalActorsFactory) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalActorsFactory: SetMachine ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateActorFromObject(Object _self, Object _value)
{
	DPUSHS ("ExternalActorsFactory: CreateActorFromObject begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateActorFromObject --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	if((LogicFactory_FromLong(_logicFactory, _value->gid == 15425740279749906432ull)) != _false)
	{
		Object toReturn = ExternalActorsFactory_CreateNumber(_self, _value);
		DPOPS ("ExternalActorsFactory: CreateActorFromObject ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, _value->gid ==  3732711262168886272ull)) != _false)
	{
		Object toReturn = ExternalActorsFactory_CreateList(_self, _value);
		DPOPS ("ExternalActorsFactory: CreateActorFromObject ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, _value->gid ==  2108332898258556672ull)) != _false)
	{
		Object toReturn = ExternalActorsFactory_CreateListMap(_self, _value);
		DPOPS ("ExternalActorsFactory: CreateActorFromObject ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, _value->gid == 15931002582760847360ull)) != _false)
	{
		Object toReturn = ExternalActorsFactory_CreateChar(_self, _value);
		DPOPS ("ExternalActorsFactory: CreateActorFromObject ended.")
		return toReturn;
	}
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Попытка создания объекта неивестного типа.", 79));
	Object toReturn = _nil;
	DPOPS ("ExternalActorsFactory: CreateActorFromObject ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateNumber(Object _self, Object _number)
{
	DPUSHS ("ExternalActorsFactory: CreateNumber begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateNumber --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:CreateNumber --- Checking for correct parameter type failed at parameter _number.", _number->gid == 15425740279749906432ull || _number == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _toReturn;
	_toReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), _uid);
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), _number, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object toReturn = _toReturn;
	DPOPS ("ExternalActorsFactory: CreateNumber ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateChar(Object _self, Object _char)
{
	DPUSHS ("ExternalActorsFactory: CreateChar begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateChar --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:CreateChar --- Checking for correct parameter type failed at parameter _char.", _char->gid ==  6707630545906071552ull || _char == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Символ", 12));
	Object _toReturn;
	_toReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), _uid);
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), _char, StringFactory_FromUTF8(_stringFactory, "Символ", 12));
	Object toReturn = _toReturn;
	DPOPS ("ExternalActorsFactory: CreateChar ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateString(Object _self, Object _string)
{
	DPUSHS ("ExternalActorsFactory: CreateString begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateString --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:CreateString --- Checking for correct parameter type failed at parameter _string.", _string->gid ==  3732711262168886272ull || _string == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Строка", 12));
	Object _toReturn;
	_toReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), _uid);
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), _string, StringFactory_FromUTF8(_stringFactory, "Строка", 12));
	Object toReturn = _toReturn;
	DPOPS ("ExternalActorsFactory: CreateString ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateList(Object _self, Object _list)
{
	DPUSHS ("ExternalActorsFactory: CreateList begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateList --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:CreateList --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Object _toReturn;
	_toReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), _uid);
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), _list, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), ExternalEntitiesFactory_CreateEmptyList(_entitiesFactory), StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object toReturn = _toReturn;
	DPOPS ("ExternalActorsFactory: CreateList ended.")
	return toReturn;
}

Object ExternalActorsFactory_CreateListMap(Object _self, Object _listMap)
{
	DPUSHS ("ExternalActorsFactory: CreateListMap begined.")
	ASSERT_C ( "ExternalActorsFactory:CreateListMap --- Checking for correct object type failed.", _self->gid ==  8965844543623282688ull )
	ASSERT_C ( "ExternalActorsFactory:CreateListMap --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	Object _uid;
	_uid = Processor_FieldNameToUID((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _toReturn;
	_toReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalActorsFactory) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), _uid);
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), _listMap, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	ListMap_ActorSetProperty(Machine_UIDToActor((((ExternalActorsFactory) (_self->entity))->_machine), _toReturn), ExternalEntitiesFactory_CreateEmptyList(_entitiesFactory), StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object toReturn = _toReturn;
	DPOPS ("ExternalActorsFactory: CreateListMap ended.")
	return toReturn;
}
