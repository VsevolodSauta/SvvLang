#include "internals/basics.h"
#include "internals/ExternalObjectManipulator/imports.h"


Object ExternalObjectManipulator_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct ExternalObjectManipulator));
	toReturn->gid =  8518571086308177920ull;
	Object_SetComparator(toReturn, &ExternalObjectManipulator_Compare);
	Object_SetDestructor(toReturn, &ExternalObjectManipulator_Destroy);
	Object_SetCloner(toReturn, &ExternalObjectManipulator_Clone);
	Object_SetDeepCloner(toReturn, &ExternalObjectManipulator_DeepClone);
	((ExternalObjectManipulator) (toReturn->entity))->_machine = _nil;
	toReturn = ExternalObjectManipulator_Init(toReturn);
	return toReturn;
}

Object ExternalObjectManipulator_Init(Object _self)
{
	return _self;
}

Object ExternalObjectManipulator_Clone(Object _self)
{
	return _self;
}

Object ExternalObjectManipulator_Destroy(Object _self)
{
	return Object_Destroy(_self);
}

Object ExternalObjectManipulator_Compare(Object _self)
{
	return _equal;
}

Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine)
{
	(((ExternalObjectManipulator) (_self->entity))->_machine) = _machine;
	return _self;
}

Object ExternalObjectManipulator_ObjectCreate(Object _self)
{
	AutoreleasePool_PushFrame(_autoreleasePool);
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Создаем объект.", 28));
	Object _object;
	_object = ListMap_Create();
	Object _messageList;
	_messageList = List_Create();
	Object _methods;
	_methods = ListMap_Create();
	Object _fields;
	_fields = ListMap_Create();
	Object _jobs;
	_jobs = List_Create();
	Object _properties;
	_properties = ListMap_Create();
	Object _uids;
	_uids = List_Create();
	Object _uid;
	_uid = Machine_GetUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	List_PushBack(_uids, _uid);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12), _methods);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Поля", 8), _fields);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Свойства", 16), _properties);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Работы", 12), _jobs);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), _messageList);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28), _uids);
	Machine_SetObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid, _object);
	Object_Release(_object);
	Object_Release(_jobs);
	Object_Release(_fields);
	Object_Release(_properties);
	Object_Release(_methods);
	Object_Release(_messageList);
	Object_Release(_uids);
	AutoreleasePool_PopFrame(_autoreleasePool);
	return _uid;
}

Object ExternalObjectManipulator_ObjectClone(Object _self, Object _uid)
{
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GetUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	Object _objectToReturn;
	_objectToReturn = Object_DeepClone(_object);
	Machine_SetObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uidToReturn, _objectToReturn);
	Object_Release(_objectToReturn);
	return _uidToReturn;
}

Object ExternalObjectManipulator_SetBasicMethodForObjectWithName(Object _self, Object _methodAdress, Object _uid, Object _name)
{
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Адрес", 10), _methodAdress);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _true);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	return _self;
}

Object ExternalObjectManipulator_SetMethodForObjectWithName(Object _self, Object _methodBody, Object _uid, Object _name)
{
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8), _methodBody);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	return _self;
}
