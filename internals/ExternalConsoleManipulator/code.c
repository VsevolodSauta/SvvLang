#include "internals/basics.h"
#include "internals/ExternalConsoleManipulator/imports.h"


Object ExternalConsoleManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalConsoleManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalConsoleManipulator));
	_self->gid =   220283697601632256ull;
	Object_SetComparator(_self, &ExternalConsoleManipulator_Compare);
	Object_SetDestructor(_self, &ExternalConsoleManipulator_Destroy);
	Object_SetCloner(_self, &ExternalConsoleManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalConsoleManipulator_DeepClone);
	((ExternalConsoleManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalConsoleManipulator_Init(_self);
	DPOPS ("ExternalConsoleManipulator: Create ended.")
	return _self;
}

Object ExternalConsoleManipulator_Init(Object _self)
{
	DPUSHS ("ExternalConsoleManipulator: Init begined.")
	ASSERT_C ( "ExternalConsoleManipulator:Init --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	Object toReturn = _self;
	DPOPS ("ExternalConsoleManipulator: Init ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalConsoleManipulator: Clone begined.")
	ASSERT_C ( "ExternalConsoleManipulator:Clone --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	Object toReturn = _self;
	DPOPS ("ExternalConsoleManipulator: Clone ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalConsoleManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalConsoleManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	Object toReturn = _self;
	DPOPS ("ExternalConsoleManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalConsoleManipulator: Destroy begined.")
	ASSERT_C ( "ExternalConsoleManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalConsoleManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_Compare(Object _self, Object _consoleManipulator)
{
	DPUSHS ("ExternalConsoleManipulator: Compare begined.")
	ASSERT_C ( "ExternalConsoleManipulator:Compare --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	ASSERT_C ( "ExternalConsoleManipulator:Compare --- Checking for correct parameter type failed at parameter _consoleManipulator.", _consoleManipulator->gid ==   220283697601632256ull || _consoleManipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalConsoleManipulator: Compare ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalConsoleManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalConsoleManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	ASSERT_C ( "ExternalConsoleManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalConsoleManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalConsoleManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_CreateUIDConsoleFromUIDObject(Object _self, Object _uid)
{
	DPUSHS ("ExternalConsoleManipulator: CreateUIDConsoleFromUIDObject begined.")
	ASSERT_C ( "ExternalConsoleManipulator:CreateUIDConsoleFromUIDObject --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	ASSERT_C ( "ExternalConsoleManipulator:CreateUIDConsoleFromUIDObject --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _object;
	_object = Machine_UIDToObject((((ExternalConsoleManipulator) (_self->entity))->_machine), _uid);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalConsoleManipulator_WriteUIDConsoleBasicMethod), StringFactory_FromUTF8(_stringFactory, "Вывести", 14));
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	Object _stage;
	_stage = ExternalEntitiesFactory_CreateEmptyJobStage(_entitiesFactory);
	ListMap_StageSetMethod(_stage, StringFactory_FromUTF8(_stringFactory, "Вывести", 14));
	ListMap_StageSetMessageSlot(_stage, StringFactory_FromUTF8(_stringFactory, "Запрос на вывод", 28));
	ListMap_StageIncrementMessagesCounter(_stage);
	ListMap_MessageSlotSetStage(_messageSlot, StringFactory_FromUTF8(_stringFactory, "Вывод", 10));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Тип", 6), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), StringFactory_FromUTF8(_stringFactory, "Вывести", 14)));
	ListMap_JobSetMessageSlot(_job, _messageSlot, StringFactory_FromUTF8(_stringFactory, "Запрос на вывод", 28));
	ListMap_JobSetStage(_job, _stage, StringFactory_FromUTF8(_stringFactory, "Вывод", 10));
	ListMap_ObjectSetJob(_object, _job, StringFactory_FromUTF8(_stringFactory, "Вывод", 10));
	Object toReturn = _uid;
	DPOPS ("ExternalConsoleManipulator: CreateUIDConsoleFromUIDObject ended.")
	return toReturn;
}

Object ExternalConsoleManipulator_WriteUIDConsoleBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalConsoleManipulator: WriteUIDConsoleBasicMethod begined.")
	ASSERT_C ( "ExternalConsoleManipulator:WriteUIDConsoleBasicMethod --- Checking for correct object type failed.", _self->gid ==   220283697601632256ull )
	ASSERT_C ( "ExternalConsoleManipulator:WriteUIDConsoleBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _string;
	_string = ListMap_JobFieldInMessageSlot(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Строка", 12), StringFactory_FromUTF8(_stringFactory, "Запрос на вывод", 28));
	Console_WriteLnString(_console, _string);
	Object _replyMessage;
	_replyMessage = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_replyMessage);
	Processor_SendReplyForMessage(_processor, _replyMessage, StringFactory_FromUTF8(_stringFactory, "Запрос на вывод", 28));
	Object toReturn = _self;
	DPOPS ("ExternalConsoleManipulator: WriteUIDConsoleBasicMethod ended.")
	return toReturn;
}
