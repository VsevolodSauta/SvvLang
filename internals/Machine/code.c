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
	_self = Machine_Init(_self);
	DPOPS ("Machine: Create ended.")
	return _self;
}

Object Machine_Init(Object _self)
{
	DPUSHS ("Machine: Init begined.")
	(((Machine) (_self->entity))->_objectsByUIDs) = ListMap_Create();
	(((Machine) (_self->entity))->_uidGenerator) = UIDGenerator_Create();
	(((Machine) (_self->entity))->_globalContext) = ListMap_Create();
	(((Machine) (_self->entity))->_processor) = Processor_Create();
	Processor_SetMachine((((Machine) (_self->entity))->_processor), _self);
	(((Machine) (_self->entity))->_scheduler) = MachineScheduler_Create();
	Object toReturn = _self;
	DPOPS ("Machine: Init ended.")
	return toReturn;
}

Object Machine_LoadApplication(Object _self, Object _applicationName)
{
	DPUSHS ("Machine: LoadApplication begined.")
	AutoreleasePool_PushFrame(_autoreleasePool);
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Загружаем приложение.", 40));
	Object _file;
	_file = File_Create();
	File_OpenForReading(_file, _applicationName);
	if((File_ErrorWhileOpenning(_file)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Возникла ошибка при загрузке приложения. Невозможно прочитать приложение.", 137));
	}
	Object _contents;
	_contents = File_ReadContentsOfFile(_file);
	File_Close(_file);
	Console_WriteLnNumber(_console, List_Size(_contents));
	Console_WriteLnString(_console, _contents);
	Object _parsedObject;
	_parsedObject = JSON_ParseObject(_json, List_First(_contents));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_parsedObject, (((JSON) (_json->entity))->_error)) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректный текст приложения. Невозможно провести грамматический разбор.", 138));
		AutoreleasePool_PopFrame(_autoreleasePool);
		Object toReturn = _self;
		DPOPS ("Machine: LoadApplication ended.")
		return toReturn;
	}
	ListMap_Add((((Machine) (_self->entity))->_globalContext), ListMap_ListAt(ListMap_ListMapAt(_parsedObject, StringFactory_FromUTF8(_stringFactory, "Объект", 12)), StringFactory_FromUTF8(_stringFactory, "Имя", 6)), _parsedObject);
	Object _uid;
	_uid = UIDGenerator_GetUID((((Machine) (_self->entity))->_uidGenerator));
	ListMap_Add((((Machine) (_self->entity))->_objectsByUIDs), _uid, _parsedObject);
	Object _uids;
	_uids = List_Create();
	ListMap_Add(_parsedObject, StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28), _uids);
	List_PushBack(_uids, _uid);
	Object_Release(_uids);
	Object _messageList;
	_messageList = List_Create();
	ListMap_Add(_parsedObject, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), _messageList);
	Object_Release(_messageList);
	MachineScheduler_Schedule((((Machine) (_self->entity))->_scheduler), _uid);
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _self;
	DPOPS ("Machine: LoadApplication ended.")
	return toReturn;
}

Object Machine_ObjectByUID(Object _self, Object _uid)
{
	DPUSHS ("Machine: ObjectByUID begined.")
	Object toReturn = ListMap_ObjectAt((((Machine) (_self->entity))->_objectsByUIDs), _uid);
	DPOPS ("Machine: ObjectByUID ended.")
	return toReturn;
}

Object Machine_SetObjectByUID(Object _self, Object _object, Object _uid)
{
	DPUSHS ("Machine: SetObjectByUID begined.")
	ListMap_Add((((Machine) (_self->entity))->_objectsByUIDs), _uid, _object);
	Object toReturn = _self;
	DPOPS ("Machine: SetObjectByUID ended.")
	return toReturn;
}

Object Machine_GetUID(Object _self)
{
	DPUSHS ("Machine: GetUID begined.")
	Object toReturn = UIDGenerator_GetUID((((Machine) (_self->entity))->_uidGenerator));
	DPOPS ("Machine: GetUID ended.")
	return toReturn;
}

Object Machine_RestorePreviousState(Object _self)
{
	DPUSHS ("Machine: RestorePreviousState begined.")
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Этот метод виртуальной машины не реализован. Не обращайте внимания. :)", 127));
	Object toReturn = _self;
	DPOPS ("Machine: RestorePreviousState ended.")
	return toReturn;
}

Object Machine_Schedule(Object _self, Object _uid)
{
	DPUSHS ("Machine: Schedule begined.")
	MachineScheduler_Schedule((((Machine) (_self->entity))->_scheduler), _uid);
	Object toReturn = _self;
	DPOPS ("Machine: Schedule ended.")
	return toReturn;
}

Object Machine_Run(Object _self)
{
	DPUSHS ("Machine: Run begined.")
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Машина запущена.", 30));
	if((_true) != _false)
	{
		Machine_LoadApplication(_self, StringFactory_FromUTF8(_stringFactory, "Приложение", 20));
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
	Object toReturn = _self;
	DPOPS ("Machine: Run ended.")
	return toReturn;
}

Object Machine_Destroy(Object _self)
{
	DPUSHS ("Machine: Destroy begined.")
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
	Object toReturn = _self;
	DPOPS ("Machine: Clone ended.")
	return toReturn;
}

Object Machine_DeepClone(Object _self)
{
	DPUSHS ("Machine: DeepClone begined.")
	Object toReturn = _self;
	DPOPS ("Machine: DeepClone ended.")
	return toReturn;
}

Object Machine_Compare(Object _self, Object _machine)
{
	DPUSHS ("Machine: Compare begined.")
	Object toReturn = _equal;
	DPOPS ("Machine: Compare ended.")
	return toReturn;
}
