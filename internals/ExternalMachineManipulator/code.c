#include "internals/basics.h"
#include "internals/ExternalMachineManipulator/imports.h"


Object ExternalMachineManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalMachineManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalMachineManipulator));
	_self->gid =  4316978841904643584ull;
	Object_SetComparator(_self, &ExternalMachineManipulator_Compare);
	Object_SetDestructor(_self, &ExternalMachineManipulator_Destroy);
	Object_SetCloner(_self, &ExternalMachineManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalMachineManipulator_DeepClone);
	((ExternalMachineManipulator) (_self->entity))->_machine = _nil;
	((ExternalMachineManipulator) (_self->entity))->_object = _nil;
	((ExternalMachineManipulator) (_self->entity))->_console = _nil;
	_self = ExternalMachineManipulator_Init(_self);
	DPOPS ("ExternalMachineManipulator: Create ended.")
	return _self;
}

Object ExternalMachineManipulator_Init(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: Init begined.")
	ASSERT_C ( "ExternalMachineManipulator:Init --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	(((ExternalMachineManipulator) (_self->entity))->_object) = ExternalObjectManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_console) = ExternalConsoleManipulator_Create();
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: Init ended.")
	return toReturn;
}

Object ExternalMachineManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: Destroy begined.")
	ASSERT_C ( "ExternalMachineManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_object));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_console));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalMachineManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalMachineManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: Clone begined.")
	ASSERT_C ( "ExternalMachineManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalMachineManipulator: Clone ended.")
	return toReturn;
}

Object ExternalMachineManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalMachineManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalMachineManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalMachineManipulator_Compare(Object _self, Object _machineManipulator)
{
	DPUSHS ("ExternalMachineManipulator: Compare begined.")
	ASSERT_C ( "ExternalMachineManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: Compare ended.")
	return toReturn;
}

Object ExternalMachineManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalMachineManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalMachineManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	(((ExternalMachineManipulator) (_self->entity))->_machine) = _machine;
	ExternalObjectManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_object), _machine);
	ExternalConsoleManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_console), _machine);
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalMachineManipulator_CreateAll(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: CreateAll begined.")
	ASSERT_C ( "ExternalMachineManipulator:CreateAll --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object _objectUID;
	_objectUID = ExternalObjectManipulator_CreateUIDObject((((ExternalMachineManipulator) (_self->entity))->_object));
	List_PrintLn(StringFactory_FromUTF8(_stringFactory, "Object created.", 15));
	Object _consoleUID;
	_consoleUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_object), _objectUID);
	List_PrintLn(StringFactory_FromUTF8(_stringFactory, "Console created.", 16));
	ExternalConsoleManipulator_CreateUIDConsoleFromUIDObject((((ExternalMachineManipulator) (_self->entity))->_console), _consoleUID);
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: CreateAll ended.")
	return toReturn;
}
