#include "internals/basics.h"
#include "internals/Machine/imports.h"


Object Machine_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Machine));
	toReturn->gid =  6547848715907434496ull;
	Object_SetComparator(toReturn, &Machine_Compare);
	Object_SetDestructor(toReturn, &Machine_Destroy);
	Object_SetCloner(toReturn, &Machine_Clone);
	((Machine) (toReturn->entity))->_objectsByUIDs = _nil;
	((Machine) (toReturn->entity))->_uidGenerator = _nil;
	((Machine) (toReturn->entity))->_globalContext = _nil;
	((Machine) (toReturn->entity))->_processor = _nil;
	((Machine) (toReturn->entity))->_scheduler = _nil;
	toReturn = Machine_Init(toReturn);
	return toReturn;
}

Object Machine_Init(Object _self)
{
	(((Machine) (_self->entity))->_objectsByUIDs) = ListMap_Create();
	(((Machine) (_self->entity))->_uidGenerator) = UIDGenerator_Create();
	(((Machine) (_self->entity))->_globalContext) = ListMap_Create();
	(((Machine) (_self->entity))->_processor) = Processor_Create();
	Processor_SetMachine((((Machine) (_self->entity))->_processor), _self);
	(((Machine) (_self->entity))->_scheduler) = MachineScheduler_Create();
	return _self;
}

Object Machine_CreateObject(Object _self)
{
	AutoreleasePool_PushFrame(_autoreleasePool);
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Создаем объект.", 28));
	Object _object;
	_object = ListMap_Create();
	Object _messageQueue;
	_messageQueue = Queue_Create();
	Object _methods;
	_methods = ListMap_Create();
	Object _fields;
	_fields = ListMap_Create();
	Object _jobs;
	_jobs = List_Create();
	Object _properties;
	_properties = ListMap_Create();
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12), _methods);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Поля", 8), _fields);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Свойства", 16), _properties);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Работы", 12), _jobs);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), _messageQueue);
	ListMap_Add((((Machine) (_self->entity))->_objectsByUIDs), UIDGenerator_getUID((((Machine) (_self->entity))->_uidGenerator)), _object);
	Object_Release(_object);
	Object_Release(_jobs);
	Object_Release(_fields);
	Object_Release(_properties);
	Object_Release(_methods);
	Object_Release(_messageQueue);
	Object def = _self;
	AutoreleasePool_PopFrame(_autoreleasePool);
	return def;
}

Object Machine_ObjectByUID(Object _self, Object _uid)
{
	return ListMap_ObjectAt((((Machine) (_self->entity))->_objectsByUIDs), _uid);
}

Object Machine_RestorePreviousState(Object _self)
{
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Этот метод виртуальной машины не реализован. Не обращайте внимания. : )", 128));
	return _self;
}

Object Machine_Schedule(Object _self, Object _object)
{
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Этот метод виртуальной машины не реализован. Не обращайте внимания. : )", 128));
	return _self;
}

Object Machine_Run(Object _self)
{
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Машина запущена.", 30));
	if((_true) != _false)
	{
		Machine_CreateObject(_self);
	}
	else
	{
		Machine_RestorePreviousState(_self);
	}
	while(1)
	{
		Object _object;
		_object = MachineScheduler_GetNextObject((((Machine) (_self->entity))->_scheduler));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_object, _nil) == _equal)) != _false)
		{
			Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Планировщик времени не выдал объект. Следовало бы уйти в ожидание, но событий больше никаких не произойдет. Выходим.", 212));
			break;
		}
		else
		{
			Processor_ProcessObject((((Machine) (_self->entity))->_processor), _object);
		}
	}
	return _self;
}

Object Machine_Destroy(Object _self)
{
	DPUSHS( "Machine: Destroying." ) 
	Object_Release((((Machine) (_self->entity))->_objectsByUIDs));
	Object_Release((((Machine) (_self->entity))->_globalContext));
	Object_Release((((Machine) (_self->entity))->_uidGenerator));
	Object_Release((((Machine) (_self->entity))->_scheduler));
	Object def = Object_Destroy(_self);
	DPOPS( "Machine: Destroyed." ) 
	return def;
}

Object Machine_Clone(Object _self)
{
	return _self;
}

Object Machine_Compare(Object _self, Object _machine)
{
	return _equal;
}
