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
	_parsedObject = JSONParser_ParseObject(_jsonParser, List_First(_contents));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_parsedObject, (((JSONParser) (_jsonParser->entity))->_error)) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректный текст объекта. Невозможно провести грамматический разбор.", 132));
		AutoreleasePool_PopFrame(_autoreleasePool);
		Object toReturn = _self;
		DPOPS ("Machine: LoadUIDWithNameToNamespace ended.")
		return toReturn;
	}
	Object _uid;
	_uid = UIDGenerator_GenerateUID((((Machine) (_self->entity))->_uidGenerator));
	Machine_SetUIDToObject(_self, _uid, _parsedObject);
	Machine_ScheduleUID(_self, _uid);
	Machine_DefineFieldHelper(_self, _uid, ListMap_ListAt(ListMap_ObjectProperties(_parsedObject), StringFactory_FromUTF8(_stringFactory, "Имя", 6)), _namespace);
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _uid;
	DPOPS ("Machine: LoadUIDWithNameToNamespace ended.")
	return toReturn;
}

Object Machine_ImportUID(Object _self, Object _objectName)
{
	DPUSHS ("Machine: ImportUID begined.")
	ASSERT_C ( "Machine:ImportUID --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:ImportUID --- Checking for correct parameter type failed at parameter _objectName.", _objectName->gid ==  3732711262168886272ull || _objectName == _nil )
	Object toReturn = Machine_LoadUIDWithNameToNamespace(_self, _objectName, (((Machine) (_self->entity))->_globalContext));
	DPOPS ("Machine: ImportUID ended.")
	return toReturn;
}

Object Machine_RegisterAtGlobalContext(Object _self, Object _uid, Object _name)
{
	DPUSHS ("Machine: RegisterAtGlobalContext begined.")
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct parameter type failed at parameter _name.", _name->gid ==  3732711262168886272ull || _name == _nil )
	Object toReturn = Machine_DefineFieldHelper(_self, _uid, _name, (((Machine) (_self->entity))->_globalContext));
	DPOPS ("Machine: RegisterAtGlobalContext ended.")
	return toReturn;
}

Object Machine_DefineFieldHelper(Object _self, Object _uid, Object _fieldName, Object _nameSpace)
{
	DPUSHS ("Machine: DefineFieldHelper begined.")
	ASSERT_C ( "Machine:DefineFieldHelper --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:DefineFieldHelper --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	ASSERT_C ( "Machine:DefineFieldHelper --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Machine:DefineFieldHelper --- Checking for correct parameter type failed at parameter _nameSpace.", _nameSpace->gid ==  2108332898258556672ull || _nameSpace == _nil )
	Object _synonim;
	_synonim = Synonim_Create();
	Synonim_SetUID(_synonim, _uid);
	Object _reference;
	_reference = ListMap_Create();
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), _nameSpace);
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _fieldName);
	Synonim_AddReference(_synonim, _reference);
	Object_Release(_reference);
	Object_Release(_synonim);
	Object toReturn = _self;
	DPOPS ("Machine: DefineFieldHelper ended.")
	return toReturn;
}

Object Machine_UIDToObject(Object _self, Object _uid)
{
	DPUSHS ("Machine: UIDToObject begined.")
	ASSERT_C ( "Machine:UIDToObject --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:UIDToObject --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object toReturn = ListMap_ObjectAt((((Machine) (_self->entity))->_objectsByUIDs), _uid);
	DPOPS ("Machine: UIDToObject ended.")
	return toReturn;
}

Object Machine_SetUIDToObject(Object _self, Object _uid, Object _object)
{
	DPUSHS ("Machine: SetUIDToObject begined.")
	ASSERT_C ( "Machine:SetUIDToObject --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:SetUIDToObject --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	ASSERT_C ( "Machine:SetUIDToObject --- Checking for correct parameter type failed at parameter _object.", _object->gid ==  2108332898258556672ull || _object == _nil )
	ListMap_Add((((Machine) (_self->entity))->_objectsByUIDs), _uid, _object);
	List_PushBack(ListMap_ListAt(ListMap_ObjectProperties(_object), StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28)), _uid);
	Object toReturn = _self;
	DPOPS ("Machine: SetUIDToObject ended.")
	return toReturn;
}

Object Machine_GenerateUID(Object _self)
{
	DPUSHS ("Machine: GenerateUID begined.")
	ASSERT_C ( "Machine:GenerateUID --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object toReturn = UIDGenerator_GenerateUID((((Machine) (_self->entity))->_uidGenerator));
	DPOPS ("Machine: GenerateUID ended.")
	return toReturn;
}

Object Machine_RestorePreviousState(Object _self)
{
	DPUSHS ("Machine: RestorePreviousState begined.")
	ASSERT_C ( "Machine:RestorePreviousState --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Этот метод виртуальной машины не реализован. Не обращайте внимания. :)", 127));
	Object toReturn = _self;
	DPOPS ("Machine: RestorePreviousState ended.")
	return toReturn;
}

Object Machine_ScheduleUID(Object _self, Object _uid)
{
	DPUSHS ("Machine: ScheduleUID begined.")
	ASSERT_C ( "Machine:ScheduleUID --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:ScheduleUID --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	MachineScheduler_ScheduleUID((((Machine) (_self->entity))->_scheduler), _uid);
	Object toReturn = _self;
	DPOPS ("Machine: ScheduleUID ended.")
	return toReturn;
}

Object Machine_Run(Object _self)
{
	DPUSHS ("Machine: Run begined.")
	ASSERT_C ( "Machine:Run --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Машина запущена.", 30));
	while(1)
	{
		Object _uid;
		_uid = MachineScheduler_GetNextUID((((Machine) (_self->entity))->_scheduler));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_uid, _nil) == _equal)) != _false)
		{
			Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Планировщик времени не выдал объект. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.", 212));
			break;
		}
		else
		{
			Processor_ProcessUID((((Machine) (_self->entity))->_processor), _uid);
		}
	}
	Object toReturn = _self;
	DPOPS ("Machine: Run ended.")
	return toReturn;
}

Object Machine_Destroy(Object _self)
{
	DPUSHS ("Machine: Destroy begined.")
	ASSERT_C ( "Machine:Destroy --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object_Release((((Machine) (_self->entity))->_objectsByUIDs));
	Object_Release((((Machine) (_self->entity))->_globalContext));
	Object_Release((((Machine) (_self->entity))->_uidGenerator));
	Object_Release((((Machine) (_self->entity))->_scheduler));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Machine: Destroy ended.")
	return toReturn;
}

Object Machine_Clone(Object _self)
{
	DPUSHS ("Machine: Clone begined.")
	ASSERT_C ( "Machine:Clone --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("Machine: Clone ended.")
	return toReturn;
}

Object Machine_DeepClone(Object _self)
{
	DPUSHS ("Machine: DeepClone begined.")
	ASSERT_C ( "Machine:DeepClone --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("Machine: DeepClone ended.")
	return toReturn;
}

Object Machine_Compare(Object _self, Object _machine)
{
	DPUSHS ("Machine: Compare begined.")
	ASSERT_C ( "Machine:Compare --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:Compare --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	Object toReturn = _equal;
	DPOPS ("Machine: Compare ended.")
	return toReturn;
}
