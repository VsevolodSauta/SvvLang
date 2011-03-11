#include "internals/basics.h"
#include "internals/Machine/imports.h"


Object Machine_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Machine: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Machine));
	_self->gid =  6547848715907434496ull;
	Object_SetComparator(_self, &Machine_Compare);
	Object_SetDestructor(_self, &Machine_Destroy);
	Object_SetCloner(_self, &Machine_Clone);
	Object_SetDeepCloner(_self, &Machine_DeepClone);
	((Machine) (_self->entity))->_objectsByUIDs = _nil;
	((Machine) (_self->entity))->_uidGenerator = _nil;
	((Machine) (_self->entity))->_globalContext = _nil;
	((Machine) (_self->entity))->_processor = _nil;
	((Machine) (_self->entity))->_scheduler = _nil;
	((Machine) (_self->entity))->_machineManipulator = _nil;
	_self = Machine_Init(_self);
	DPOPS ("Machine: Create ended.")
	return _self;
}

Object Machine_Init(Object _self)
{
	DPUSHS ("Machine: Init begined.")
	ASSERT_C ( "Machine:Init --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	(((Machine) (_self->entity))->_objectsByUIDs) = ListMap_Create();
	(((Machine) (_self->entity))->_uidGenerator) = UIDGenerator_Create();
	(((Machine) (_self->entity))->_globalContext) = ListMap_Create();
	(((Machine) (_self->entity))->_processor) = Processor_Create();
	Processor_SetMachine((((Machine) (_self->entity))->_processor), _self);
	(((Machine) (_self->entity))->_scheduler) = MachineScheduler_Create();
	(((Machine) (_self->entity))->_machineManipulator) = ExternalMachineManipulator_Create();
	ExternalMachineManipulator_SetMachine((((Machine) (_self->entity))->_machineManipulator), _self);
	ExternalMachineManipulator_CreateAll((((Machine) (_self->entity))->_machineManipulator));
	Object _file;
	_file = File_Create();
	File_OpenForAppending(_file, StringFactory_FromUTF8(_stringFactory, "Vasia", 5));
	File_WriteNakedString(_file, StringFactory_FromUTF8(_stringFactory, "Vasia porosya", 13));
	File_Close(_file);
	Object toReturn = _self;
	DPOPS ("Machine: Init ended.")
	return toReturn;
}

Object Machine_LoadUIDWithNameToNamespace(Object _self, Object _objectName, Object _namespace)
{
	DPUSHS ("Machine: LoadUIDWithNameToNamespace begined.")
	ASSERT_C ( "Machine:LoadUIDWithNameToNamespace --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:LoadUIDWithNameToNamespace --- Checking for correct parameter type failed at parameter _objectName.", _objectName->gid ==  3732711262168886272ull || _objectName == _nil )
	ASSERT_C ( "Machine:LoadUIDWithNameToNamespace --- Checking for correct parameter type failed at parameter _namespace.", _namespace->gid ==  2108332898258556672ull || _namespace == _nil )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Загружаем объект ", 32));
	Console_WriteLnString(_console, _objectName);
	Object _file;
	_file = File_Create();
	File_OpenForReading(_file, _objectName);
	if((File_ErrorWhileOpenning(_file)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Возникла ошибка при загрузке объекта. Невозможно прочитать контейнер объекта (как правило файл).", 177));
	}
	Object _contents;
	_contents = File_ReadContentsOfFile(_file);
	File_Close(_file);
	Object _parsedObject;
	Object _jsonParser;
