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
	((Machine) (_self->entity))->_actorsByUIDs = _nil;
	((Machine) (_self->entity))->_uidGenerator = _nil;
	((Machine) (_self->entity))->_globalContext = _nil;
	((Machine) (_self->entity))->_fakeProcessor = _nil;
	((Machine) (_self->entity))->_processors = _nil;
	((Machine) (_self->entity))->_scheduler = _nil;
	((Machine) (_self->entity))->_machineManipulator = _nil;
	((Machine) (_self->entity))->_totalProcessors = _nil;
	((Machine) (_self->entity))->_actorsFactory = _nil;
	_self = Machine_Init(_self);
	DPOPS ("Machine: Create ended.")
	return _self;
}

Object Machine_Init(Object _self)
{
	DPUSHS ("Machine: Init begined.")
	ASSERT_C ( "Machine:Init --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	(((Machine) (_self->entity))->_actorsFactory) = ExternalActorsFactory_Create();
	ExternalActorsFactory_SetMachine((((Machine) (_self->entity))->_actorsFactory), _self);
	Object_SetRetaining(&(((Machine) (_self->entity))->_totalProcessors), NumberFactory_FromLong(_numberFactory, 1));
	(((Machine) (_self->entity))->_actorsByUIDs) = ListMap_Create();
	(((Machine) (_self->entity))->_uidGenerator) = UIDGenerator_Create();
	(((Machine) (_self->entity))->_globalContext) = ListMap_Create();
	(((Machine) (_self->entity))->_fakeProcessor) = Processor_Create();
	Processor_SetMachine((((Machine) (_self->entity))->_fakeProcessor), _self);
	(((Machine) (_self->entity))->_processors) = List_Create();
	Object _i;
	_i = NumberFactory_FromLong(_numberFactory, 0);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_i, (((Machine) (_self->entity))->_totalProcessors)) == _less)) != _false)
	{
		Object _processor;
		_processor = Processor_Create();
		Processor_SetMachine(_processor, _self);
		List_PushBack((((Machine) (_self->entity))->_processors), _processor);
		Object_Release(_processor);
		Number_Inc(_i);
	}
	(((Machine) (_self->entity))->_scheduler) = MachineScheduler_Create();
	(((Machine) (_self->entity))->_machineManipulator) = ExternalMachineManipulator_Create();
	ExternalMachineManipulator_SetMachine((((Machine) (_self->entity))->_machineManipulator), _self);
	ExternalMachineManipulator_CreateAll((((Machine) (_self->entity))->_machineManipulator));
	Object toReturn = _self;
	DPOPS ("Machine: Init ended.")
	return toReturn;
}

Object Machine_Destroy(Object _self)
{
	DPUSHS ("Machine: Destroy begined.")
	ASSERT_C ( "Machine:Destroy --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object_Release((((Machine) (_self->entity))->_actorsByUIDs));
	Object_Release((((Machine) (_self->entity))->_globalContext));
	Object_Release((((Machine) (_self->entity))->_uidGenerator));
	Object_Release((((Machine) (_self->entity))->_scheduler));
	Object_Release((((Machine) (_self->entity))->_processors));
	Object_Release((((Machine) (_self->entity))->_fakeProcessor));
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

Object Machine_ActorsFactory(Object _self)
{
	DPUSHS ("Machine: ActorsFactory begined.")
	ASSERT_C ( "Machine:ActorsFactory --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Object toReturn = (((Machine) (_self->entity))->_actorsFactory);
	DPOPS ("Machine: ActorsFactory ended.")
	return toReturn;
}

Object Machine_LoadActorWithNameToNamespace(Object _self, Object _actorName, Object _namespace)
{
	DPUSHS ("Machine: LoadActorWithNameToNamespace begined.")
	ASSERT_C ( "Machine:LoadActorWithNameToNamespace --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:LoadActorWithNameToNamespace --- Checking for correct parameter type failed at parameter _actorName.", _actorName->gid ==  3732711262168886272ull || _actorName == _nil )
	ASSERT_C ( "Machine:LoadActorWithNameToNamespace --- Checking for correct parameter type failed at parameter _namespace.", _namespace->gid ==  2108332898258556672ull || _namespace == _nil )
	AutoreleasePool_PushFrame(ThreadManager_AutoreleasePool(_threadManager));
	Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Загружаем актор ", 30));
	Console_WriteLnString(_console, _actorName);
	Object _file;
	_file = File_Create();
	File_OpenForReading(_file, _actorName);
	if((File_ErrorWhileOpenning(_file)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Возникла ошибка при загрузке объекта. Невозможно прочитать контейнер объекта (как правило файл).", 177));
	}
	Object _contents;
	_contents = File_ReadContentsOfFile(_file);
	File_Close(_file);
	Object _parsedActor;
	_parsedActor = JSONParser_ParseObject(_jsonParser, List_First(_contents));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_parsedActor, (((JSONParser) (_jsonParser->entity))->_error)) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректный текст объекта. Невозможно провести грамматический разбор.", 132));
		AutoreleasePool_PopFrame(ThreadManager_AutoreleasePool(_threadManager));
		Object toReturn = _self;
		DPOPS ("Machine: LoadActorWithNameToNamespace ended.")
		return toReturn;
	}
	Object _uid;
	_uid = UIDGenerator_GenerateUID((((Machine) (_self->entity))->_uidGenerator));
	Machine_SetUIDToActor(_self, _uid, _parsedActor);
	Machine_ScheduleUID(_self, _uid);
	Processor_DefineFieldInNameSpaceWithUID((((Machine) (_self->entity))->_fakeProcessor), ListMap_ListAt(ListMap_ActorProperties(_parsedActor), StringFactory_FromUTF8(_stringFactory, "Имя", 6)), _namespace, _uid);
	AutoreleasePool_PopFrame(ThreadManager_AutoreleasePool(_threadManager));
	Object toReturn = _uid;
	DPOPS ("Machine: LoadActorWithNameToNamespace ended.")
	return toReturn;
}

Object Machine_ImportActor(Object _self, Object _actorName)
{
	DPUSHS ("Machine: ImportActor begined.")
	ASSERT_C ( "Machine:ImportActor --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:ImportActor --- Checking for correct parameter type failed at parameter _actorName.", _actorName->gid ==  3732711262168886272ull || _actorName == _nil )
	Object toReturn = Machine_LoadActorWithNameToNamespace(_self, _actorName, (((Machine) (_self->entity))->_globalContext));
	DPOPS ("Machine: ImportActor ended.")
	return toReturn;
}

Object Machine_RegisterAtGlobalContext(Object _self, Object _uid, Object _name)
{
	DPUSHS ("Machine: RegisterAtGlobalContext begined.")
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	ASSERT_C ( "Machine:RegisterAtGlobalContext --- Checking for correct parameter type failed at parameter _name.", _name->gid ==  3732711262168886272ull || _name == _nil )
	Processor_DefineFieldInNameSpaceWithUID((((Machine) (_self->entity))->_fakeProcessor), _name, (((Machine) (_self->entity))->_globalContext), _uid);
	Object toReturn = _self;
	DPOPS ("Machine: RegisterAtGlobalContext ended.")
	return toReturn;
}

Object Machine_UIDToActor(Object _self, Object _uid)
{
	DPUSHS ("Machine: UIDToActor begined.")
	ASSERT_C ( "Machine:UIDToActor --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:UIDToActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object toReturn = ListMap_ObjectAt((((Machine) (_self->entity))->_actorsByUIDs), _uid);
	DPOPS ("Machine: UIDToActor ended.")
	return toReturn;
}

Object Machine_SetUIDToActor(Object _self, Object _uid, Object _actor)
{
	DPUSHS ("Machine: SetUIDToActor begined.")
	ASSERT_C ( "Machine:SetUIDToActor --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:SetUIDToActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	ASSERT_C ( "Machine:SetUIDToActor --- Checking for correct parameter type failed at parameter _actor.", _actor->gid ==  2108332898258556672ull || _actor == _nil )
	ListMap_Add((((Machine) (_self->entity))->_actorsByUIDs), _uid, _actor);
	List_PushBack(ListMap_ListAt(ListMap_ActorProperties(_actor), StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28)), _uid);
	Object toReturn = _self;
	DPOPS ("Machine: SetUIDToActor ended.")
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

Object Machine_ProcessorFinishedWork(Object _self, Object _processor)
{
	DPUSHS ("Machine: ProcessorFinishedWork begined.")
	ASSERT_C ( "Machine:ProcessorFinishedWork --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:ProcessorFinishedWork --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	List_PushBack((((Machine) (_self->entity))->_processors), _processor);
	Object toReturn = _self;
	DPOPS ("Machine: ProcessorFinishedWork ended.")
	return toReturn;
}

Object Machine_Run(Object _self)
{
	DPUSHS ("Machine: Run begined.")
	ASSERT_C ( "Machine:Run --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Машина запущена.", 30));
	while(1)
	{
		Object _allProcessorsAreIdling;
		_allProcessorsAreIdling = _no;
		if((List_Empty((((Machine) (_self->entity))->_processors))) != _false)
		{
			OSwait4 ( -1, 0, 0, 0 ) ; 
		}
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size((((Machine) (_self->entity))->_processors)), (((Machine) (_self->entity))->_totalProcessors)) == _equal)) != _false)
		{
			_allProcessorsAreIdling = _yes;
		}
		Object _processor;
		_processor = List_PopBack((((Machine) (_self->entity))->_processors));
		Object _uid;
		_uid = MachineScheduler_GetNextUID((((Machine) (_self->entity))->_scheduler));
		if((Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare(_uid, _nil) == _equal), _allProcessorsAreIdling)) != _false)
		{
			Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Планировщик времени не выдал объект, все объекты ожидают. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.", 250));
			break;
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_uid, _nil) != _equal)) != _false)
		{
			Processor_ProcessUID(_processor, _uid);
		}
		else
		{
			List_PushBack((((Machine) (_self->entity))->_processors), _processor);
			OSwait4 ( -1, 0, 0, 0 ) ; 
		}
	}
	Object toReturn = _self;
	DPOPS ("Machine: Run ended.")
	return toReturn;
}

Object Machine_CollectGarbageProcessListMap(Object _self, Object _listMap, Object _notToDeleteList)
{
	DPUSHS ("Machine: CollectGarbageProcessListMap begined.")
	ASSERT_C ( "Machine:CollectGarbageProcessListMap --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:CollectGarbageProcessListMap --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	ASSERT_C ( "Machine:CollectGarbageProcessListMap --- Checking for correct parameter type failed at parameter _notToDeleteList.", _notToDeleteList->gid ==  3732711262168886272ull || _notToDeleteList == _nil )
	Object _iterator;
	_iterator = ListMap_First(_listMap);
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, ListMapIterator_ThisValue(_iterator)->gid ==  3732711262168886272ull)) != _false)
		{
			Machine_CollectGarbageProcessList(_self, ListMapIterator_ThisValue(_iterator), _notToDeleteList);
		}
		else if((LogicFactory_FromLong(_logicFactory, ListMapIterator_ThisValue(_iterator)->gid ==  2108332898258556672ull)) != _false)
		{
			Machine_CollectGarbageProcessListMap(_self, ListMapIterator_ThisValue(_iterator), _notToDeleteList);
		}
		ListMapIterator_Next(_iterator);
	}
	Object toReturn = _self;
	DPOPS ("Machine: CollectGarbageProcessListMap ended.")
	return toReturn;
}

Object Machine_CollectGarbageProcessList(Object _self, Object _list, Object _notToDeleteList)
{
	DPUSHS ("Machine: CollectGarbageProcessList begined.")
	ASSERT_C ( "Machine:CollectGarbageProcessList --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	ASSERT_C ( "Machine:CollectGarbageProcessList --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	ASSERT_C ( "Machine:CollectGarbageProcessList --- Checking for correct parameter type failed at parameter _notToDeleteList.", _notToDeleteList->gid ==  3732711262168886272ull || _notToDeleteList == _nil )
	if((List_LooksLikeString(_list)) != _false)
	{
		List_PushBackIfAbsent(_notToDeleteList, _list);
	}
	else
	{
		Object _iterator;
		_iterator = List_First(_list);
		while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, ListIterator_ThisData(_iterator)->gid ==  3732711262168886272ull)) != _false)
			{
				Machine_CollectGarbageProcessList(_self, ListIterator_ThisData(_iterator), _notToDeleteList);
			}
			else if((LogicFactory_FromLong(_logicFactory, ListIterator_ThisData(_iterator)->gid ==  2108332898258556672ull)) != _false)
			{
				Machine_CollectGarbageProcessListMap(_self, ListIterator_ThisData(_iterator), _notToDeleteList);
			}
			ListIterator_Next(_iterator);
		}
	}
	Object toReturn = _self;
	DPOPS ("Machine: CollectGarbageProcessList ended.")
	return toReturn;
}

Object Machine_CollectGarbage(Object _self)
{
	DPUSHS ("Machine: CollectGarbage begined.")
	ASSERT_C ( "Machine:CollectGarbage --- Checking for correct object type failed.", _self->gid ==  6547848715907434496ull )
	AutoreleasePool_PushFrame(ThreadManager_AutoreleasePool(_threadManager));
	Object _notToDeleteList;
	_notToDeleteList = List_Create();
	Object _iterator1;
	_iterator1 = ListMap_First((((Machine) (_self->entity))->_globalContext));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator1))) != _false)
	{
		List_PushBack(_notToDeleteList, Synonim_GetUID(ListMapIterator_ThisValue(_iterator1)));
		ListMapIterator_Next(_iterator1);
	}
	_iterator1 = ListMap_First((((Machine) (_self->entity))->_actorsByUIDs));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator1))) != _false)
	{
		Object _iterator2;
		_iterator2 = ListMap_ActorJobsIterator(ListMapIterator_ListMapData(_iterator1));
		while((Logic_Not(ListMapIterator_ThisEnd(_iterator2))) != _false)
		{
			Object _iterator3;
			_iterator3 = ListMap_JobMessageSlotsIterator(ListMapIterator_ListMapData(_iterator2));
			while((Logic_Not(ListMapIterator_ThisEnd(_iterator3))) != _false)
			{
				Object _iterator4;
				_iterator4 = List_First(ListMap_MessageSlotMessages(ListMapIterator_ListMapData(_iterator3)));
				while((Logic_Not(ListIterator_ThisEnd(_iterator4))) != _false)
				{
					Object _message;
					_message = ListIterator_ListMapData(_iterator4);
					Machine_CollectGarbageProcessListMap(_self, _message, _notToDeleteList);
					ListIterator_Next(_iterator4);
				}
				ListMapIterator_Next(_iterator3);
			}
			ListMapIterator_Next(_iterator2);
		}
		ListMapIterator_Next(_iterator1);
	}
	_iterator1 = List_First(_notToDeleteList);
	while((Logic_Not(ListIterator_ThisEnd(_iterator1))) != _false)
	{
		Object _actor;
		_actor = Machine_UIDToActor(_self, ListIterator_ThisData(_iterator1));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actor, _nil) != _equal)) != _false)
		{
			Object _iterator2;
			_iterator2 = ListMap_First(ListMap_ActorFields(_actor));
			while((Logic_Not(ListMapIterator_ThisEnd(_iterator2))) != _false)
			{
				List_PushBackIfAbsent(_notToDeleteList, Synonim_GetUID(ListMapIterator_ThisValue(_iterator2)));
				ListMapIterator_Next(_iterator2);
			}
			_iterator2 = ListMap_First(ListMap_ActorJobs(_actor));
			while((Logic_Not(ListMapIterator_ThisEnd(_iterator2))) != _false)
			{
				Object _iterator3;
				_iterator3 = ListMap_First(ListMap_ActorFields(ListMapIterator_ListMapData(_iterator2)));
				while((Logic_Not(ListMapIterator_ThisEnd(_iterator3))) != _false)
				{
					List_PushBackIfAbsent(_notToDeleteList, Synonim_GetUID(ListMapIterator_ThisValue(_iterator3)));
					ListMapIterator_Next(_iterator3);
				}
				ListMapIterator_Next(_iterator2);
			}
		}
		ListIterator_Next(_iterator1);
	}
	Object _toDeleteList;
	_toDeleteList = List_Create();
	_iterator1 = ListMap_First((((Machine) (_self->entity))->_actorsByUIDs));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator1))) != _false)
	{
		if((Logic_Not(List_Contains(_notToDeleteList, ListMapIterator_ThisKey(_iterator1)))) != _false)
		{
			List_PushBack(_toDeleteList, ListMapIterator_ThisKey(_iterator1));
		}
		ListMapIterator_Next(_iterator1);
	}
	_iterator1 = List_First(_toDeleteList);
	while((Logic_Not(ListIterator_ThisEnd(_iterator1))) != _false)
	{
		List_PrintLn(ListIterator_ListData(_iterator1));
		ListMap_Remove((((Machine) (_self->entity))->_actorsByUIDs), ListIterator_ListData(_iterator1));
		ListIterator_Next(_iterator1);
	}
	Object_Release(_notToDeleteList);
	Object_Release(_toDeleteList);
	AutoreleasePool_PopFrame(ThreadManager_AutoreleasePool(_threadManager));
	Object toReturn = _self;
	DPOPS ("Machine: CollectGarbage ended.")
	return toReturn;
}
