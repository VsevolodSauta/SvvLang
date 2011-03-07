#include "internals/basics.h"
#include "internals/ExternalObjectManipulator/imports.h"


Object ExternalObjectManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalObjectManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalObjectManipulator));
	_self->gid =  8518571086308177920ull;
	Object_SetComparator(_self, &ExternalObjectManipulator_Compare);
	Object_SetDestructor(_self, &ExternalObjectManipulator_Destroy);
	Object_SetCloner(_self, &ExternalObjectManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalObjectManipulator_DeepClone);
	((ExternalObjectManipulator) (_self->entity))->_machine = _nil;
	((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy = _nil;
	_self = ExternalObjectManipulator_Init(_self);
	DPOPS ("ExternalObjectManipulator: Create ended.")
	return _self;
}

Object ExternalObjectManipulator_Init(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Init begined.")
	ASSERT_C ( "ExternalObjectManipulator:Init --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Init ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Clone begined.")
	ASSERT_C ( "ExternalObjectManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalObjectManipulator: Clone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalObjectManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalObjectManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Destroy begined.")
	ASSERT_C ( "ExternalObjectManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	Object_Release((((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalObjectManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalObjectManipulator: Compare begined.")
	ASSERT_C ( "ExternalObjectManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	ASSERT_C ( "ExternalObjectManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  8518571086308177920ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalObjectManipulator: Compare ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalObjectManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalObjectManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	ASSERT_C ( "ExternalObjectManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalObjectManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CreateUIDObject(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: CreateUIDObject begined.")
	ASSERT_C ( "ExternalObjectManipulator:CreateUIDObject --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _uid;
	_uid = Machine_ImportUID((((ExternalObjectManipulator) (_self->entity))->_machine), StringFactory_FromUTF8(_stringFactory, "SvvLanguage_C/externals/Объект", 36));
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalObjectManipulator_CloneUIDObjectBasicMethod), StringFactory_FromUTF8(_stringFactory, "Клонирование Тип=ЗапросЗапрос=Клонировать", 79));
	(((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy) = Object_DeepClone(Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid));
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _uid;
	DPOPS ("ExternalObjectManipulator: CreateUIDObject ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CloneUIDObjectInternalRoutine(Object _self, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: CloneUIDObjectInternalRoutine begined.")
	ASSERT_C ( "ExternalObjectManipulator:CloneUIDObjectInternalRoutine --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	ASSERT_C ( "ExternalObjectManipulator:CloneUIDObjectInternalRoutine --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GenerateUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	Object _objectToReturn;
	_objectToReturn = Object_DeepClone((((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy));
	ListMap_ObjectResetMethodsDestructive(_objectToReturn, Object_TempDeepClone(ListMap_ObjectMethods(_object)));
	ListMap_ObjectResetFieldsDestructive(_objectToReturn, Object_TempDeepClone(ListMap_ObjectFields(_object)));
	ListMap_ObjectRemoveAllIdentifiers(_objectToReturn);
	Machine_SetUIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uidToReturn, _objectToReturn);
	Object_Release(_objectToReturn);
	Object toReturn = _uidToReturn;
	DPOPS ("ExternalObjectManipulator: CloneUIDObjectInternalRoutine ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CloneUIDObjectBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalObjectManipulator: CloneUIDObjectBasicMethod begined.")
	ASSERT_C ( "ExternalObjectManipulator:CloneUIDObjectBasicMethod --- Checking for correct object type failed.", _self->gid ==  8518571086308177920ull )
	ASSERT_C ( "ExternalObjectManipulator:CloneUIDObjectBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _uidToReturn;
	_uidToReturn = ExternalObjectManipulator_CloneUIDObjectInternalRoutine(_self, (((Processor) (_processor->entity))->_contextUID));
	Object _replyMessage;
	_replyMessage = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_replyMessage);
	ListMap_Add(_replyMessage, StringFactory_FromUTF8(_stringFactory, "Клон", 8), _uidToReturn);
	Processor_SendReplyForMessage(_processor, _replyMessage, StringFactory_FromUTF8(_stringFactory, "Клонировать ", 23));
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: CloneUIDObjectBasicMethod ended.")
	return toReturn;
}
