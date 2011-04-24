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
	((ExternalMachineManipulator) (_self->entity))->_file = _nil;
	((ExternalMachineManipulator) (_self->entity))->_number = _nil;
	((ExternalMachineManipulator) (_self->entity))->_list = _nil;
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
	(((ExternalMachineManipulator) (_self->entity))->_file) = ExternalFileManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_number) = ExternalNumberManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_list) = ExternalListManipulator_Create();
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
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_file));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_number));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_list));
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
	ASSERT_C ( "ExternalMachineManipulator:Compare --- Checking for correct parameter type failed at parameter _machineManipulator.", _machineManipulator->gid ==  4316978841904643584ull || _machineManipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalMachineManipulator: Compare ended.")
	return toReturn;
}

Object ExternalMachineManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalMachineManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalMachineManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	ASSERT_C ( "ExternalMachineManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalMachineManipulator) (_self->entity))->_machine) = _machine;
	ExternalObjectManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_object), _machine);
	ExternalConsoleManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_console), _machine);
	ExternalFileManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_file), _machine);
	ExternalNumberManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_number), _machine);
	ExternalListManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_list), _machine);
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
	Object _consoleUID;
	_consoleUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_object), _objectUID);
	ExternalConsoleManipulator_CreateUIDConsoleFromUIDObject((((ExternalMachineManipulator) (_self->entity))->_console), _consoleUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _consoleUID, StringFactory_FromUTF8(_stringFactory, "Консоль", 14));
	Object _fileUID;
	_fileUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_object), _objectUID);
	ExternalFileManipulator_CreateUIDFileFromUIDObject((((ExternalMachineManipulator) (_self->entity))->_file), _fileUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _fileUID, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object _numberUID;
	_numberUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_object), _objectUID);
	ExternalNumberManipulator_CreateUIDNumberFromUIDObject((((ExternalMachineManipulator) (_self->entity))->_number), _numberUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _numberUID, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _listUID;
	_listUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_object), _objectUID);
	ExternalListManipulator_CreateUIDListFromUIDObject((((ExternalMachineManipulator) (_self->entity))->_list), _listUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _listUID, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ObjectJobs(Machine_UIDToObject((((ExternalMachineManipulator) (_self->entity))->_machine), _objectUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ObjectJobs(Machine_UIDToObject((((ExternalMachineManipulator) (_self->entity))->_machine), _consoleUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ObjectJobs(Machine_UIDToObject((((ExternalMachineManipulator) (_self->entity))->_machine), _fileUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ObjectJobs(Machine_UIDToObject((((ExternalMachineManipulator) (_self->entity))->_machine), _numberUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ObjectJobs(Machine_UIDToObject((((ExternalMachineManipulator) (_self->entity))->_machine), _listUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: CreateAll ended.")
	return toReturn;
}
