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
	((ExternalMachineManipulator) (_self->entity))->_actor = _nil;
	((ExternalMachineManipulator) (_self->entity))->_console = _nil;
	((ExternalMachineManipulator) (_self->entity))->_file = _nil;
	((ExternalMachineManipulator) (_self->entity))->_number = _nil;
	((ExternalMachineManipulator) (_self->entity))->_list = _nil;
	((ExternalMachineManipulator) (_self->entity))->_listMap = _nil;
	((ExternalMachineManipulator) (_self->entity))->_char = _nil;
	((ExternalMachineManipulator) (_self->entity))->_jsonParser = _nil;
	_self = ExternalMachineManipulator_Init(_self);
	DPOPS ("ExternalMachineManipulator: Create ended.")
	return _self;
}

Object ExternalMachineManipulator_Init(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: Init begined.")
	ASSERT_C ( "ExternalMachineManipulator:Init --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	(((ExternalMachineManipulator) (_self->entity))->_actor) = ExternalActorManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_console) = ExternalConsoleManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_file) = ExternalFileManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_number) = ExternalNumberManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_list) = ExternalListManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_listMap) = ExternalListMapManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_char) = ExternalCharManipulator_Create();
	(((ExternalMachineManipulator) (_self->entity))->_jsonParser) = ExternalJSONParserManipulator_Create();
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: Init ended.")
	return toReturn;
}

Object ExternalMachineManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: Destroy begined.")
	ASSERT_C ( "ExternalMachineManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_actor));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_console));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_file));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_number));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_list));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_listMap));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_char));
	Object_Release((((ExternalMachineManipulator) (_self->entity))->_jsonParser));
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
	ExternalActorManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_actor), _machine);
	ExternalConsoleManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_console), _machine);
	ExternalFileManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_file), _machine);
	ExternalNumberManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_number), _machine);
	ExternalListManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_list), _machine);
	ExternalListMapManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_listMap), _machine);
	ExternalCharManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_char), _machine);
	ExternalJSONParserManipulator_SetMachine((((ExternalMachineManipulator) (_self->entity))->_jsonParser), _machine);
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalMachineManipulator_CreateAll(Object _self)
{
	DPUSHS ("ExternalMachineManipulator: CreateAll begined.")
	ASSERT_C ( "ExternalMachineManipulator:CreateAll --- Checking for correct object type failed.", _self->gid ==  4316978841904643584ull )
	Object _actorUID;
	_actorUID = ExternalActorManipulator_CreateUIDActor((((ExternalMachineManipulator) (_self->entity))->_actor));
	Object _consoleUID;
	_consoleUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalConsoleManipulator_CreateUIDConsoleFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_console), _consoleUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _consoleUID, StringFactory_FromUTF8(_stringFactory, "Консоль", 14));
	Object _fileUID;
	_fileUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalFileManipulator_CreateUIDFileFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_file), _fileUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _fileUID, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object _numberUID;
	_numberUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalNumberManipulator_CreateUIDNumberFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_number), _numberUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _numberUID, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _listUID;
	_listUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalListManipulator_CreateUIDListFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_list), _listUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _listUID, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Object _listMapUID;
	_listMapUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalListMapManipulator_CreateUIDListMapFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_listMap), _listMapUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _listMapUID, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _charUID;
	_charUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalCharManipulator_CreateUIDCharFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_char), _charUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _charUID, StringFactory_FromUTF8(_stringFactory, "Символ", 12));
	Object _jsonParserUID;
	_jsonParserUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) (_self->entity))->_actor), _actorUID);
	ExternalJSONParserManipulator_CreateUIDJSONParserFromUIDActor((((ExternalMachineManipulator) (_self->entity))->_jsonParser), _charUID);
	Machine_RegisterAtGlobalContext((((ExternalMachineManipulator) (_self->entity))->_machine), _jsonParserUID, StringFactory_FromUTF8(_stringFactory, "Создатель объектов", 35));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _actorUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _consoleUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _fileUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _numberUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _listUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _listMapUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _charUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	ListMap_DumpKeys(ListMap_ActorJobs(Machine_UIDToActor((((ExternalMachineManipulator) (_self->entity))->_machine), _jsonParserUID)));
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "===============", 15));
	Object toReturn = _self;
	DPOPS ("ExternalMachineManipulator: CreateAll ended.")
	return toReturn;
}
