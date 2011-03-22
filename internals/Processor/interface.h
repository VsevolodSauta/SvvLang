typedef struct Processor {
	Object _contextUID;
	Object _contextJobName;
	Object _contextJobStageName;
	Object _machine;
	Object _localNamespaces;
	Object _helperStack;
	Object _processorCodes;
} *Processor;

Object Processor_Create(void);
Object Processor_Clone(Object _self);
Object Processor_DeepClone(Object _self);
Object Processor_Destroy(Object _self);
Object Processor_Compare(Object _self, Object _processor);
Object Processor_SetMachine(Object _self, Object _machine);
Object Processor_ContextObject(Object _self);
Object Processor_ContextJob(Object _self);
Object Processor_ContextJobStage(Object _self);
Object Processor_Init(Object _self);
Object Processor_Do(Object _self, Object _toDo);
Object Processor_GetNamedEntityFromToDoOrStack(Object _self, Object _entityName, Object _toDo);
Object Processor_CodeDo(Object _self, Object _toDo);
Object Processor_CodeEntityFromMessageField(Object _self, Object _toDo);
Object Processor_CodeUIDFromField(Object _self, Object _toDo);
Object Processor_CodeAddCurrentUIDToStack(Object _self, Object _toDo);
Object Processor_CodeAddCurrentJobToStack(Object _self, Object _toDo);
Object Processor_CodeAddCurrentJobStageToStack(Object _self, Object _toDo);
Object Processor_CodeAddListToStack(Object _self, Object _toDo);
Object Processor_CodeAddListMapToStack(Object _self, Object _toDo);
Object Processor_CodeRemoveFromStack(Object _self, Object _toDo);
Object Processor_CodeAddEntityToListMap(Object _self, Object _toDo);
Object Processor_CodeRemoveEntityFromListMapByKey(Object _self, Object _toDo);
Object Processor_CodeRemoveEntityFromListMapByValue(Object _self, Object _toDo);
Object Processor_CodeAddEntityToList(Object _self, Object _toDo);
Object Processor_CodeRemoveEntityFromListByPosition(Object _self, Object _toDo);
Object Processor_CodeRemoveEntityFromListByValue(Object _self, Object _toDo);
Object Processor_CodeAddEntityToStack(Object _self, Object _toDo);
Object Processor_CodeDuplicateTopInStack(Object _self, Object _toDo);
Object Processor_CodeSwapTopInStack(Object _self, Object _toDo);
Object Processor_CodeSendMessageToUID(Object _self, Object _toDo);
Object Processor_CodeSendMessageToField(Object _self, Object _toDo);
Object Processor_CodeSendMessageToMessageField(Object _self, Object _toDo);
Object Processor_CodeSendReplyForMessage(Object _self, Object _toDo);
Object Processor_CodeInvokeMethod(Object _self, Object _toDo);
Object Processor_CodeDefineMethod(Object _self, Object _toDo);
Object Processor_CodeUnDefineMethod(Object _self, Object _toDo);
Object Processor_CodeDefineLocalField(Object _self, Object _toDo);
Object Processor_CodeDefineJobField(Object _self, Object _toDo);
Object Processor_CodeDefineObjectField(Object _self, Object _toDo);
Object Processor_CodeDefineGlobalField(Object _self, Object _toDo);
Object Processor_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace);
Object Processor_CodeSetField(Object _self, Object _toDo);
Object Processor_CodeUniteField(Object _self, Object _toDo);
Object Processor_CodeUnDefineField(Object _self, Object _toDo);
Object Processor_CodeAddJob(Object _self, Object _toDo);
Object Processor_CodeFinishThisJob(Object _self, Object _toDo);
Object Processor_CodeAddJobStage(Object _self, Object _toDo);
Object Processor_CodeAddMessageSlot(Object _self, Object _toDo);
Object Processor_CodeBlockStage(Object _self, Object _toDo);
Object Processor_CodeUnBlockStage(Object _self, Object _toDo);
Object Processor_CodeBlockMessageSlot(Object _self, Object _toDo);
Object Processor_CodeUnBlockMessageSlot(Object _self, Object _toDo);
Object Processor_CodeRemoveJobStage(Object _self, Object _toDo);
Object Processor_CodeRemoveMessageSlot(Object _self, Object _toDo);
Object Processor_CodeRemoveMessageInMessageSlot(Object _self, Object _toDo);
Object Processor_CodeRemoveAllMessagesOfCurrentStageForCurrentStage(Object _self, Object _toDo);
Object Processor_CodeRemoveAllMessagesOfCurrentStageForAllStages(Object _self, Object _toDo);
Object Processor_CodeRemoveAllMessagesOfAllOpenedStages(Object _self, Object _toDo);
Object Processor_CodeRemoveAllReceivedMessages(Object _self, Object _toDo);
Object Processor_CodeRemoveAllStages(Object _self, Object _toDo);
Object Processor_CodeRemoveAllMessageSlots(Object _self, Object _toDo);
Object Processor_CodeRemoveAllStagesAndMessageSlots(Object _self, Object _toDo);
Object Processor_CodeAttachToStageMessageSlot(Object _self, Object _toDo);
Object Processor_DefineMethod(Object _self, Object _method, Object _methodName);
Object Processor_UnDefineMethod(Object _self, Object _methodName);
Object Processor_DefineFieldInNameSpaceWithUID(Object _self, Object _fieldName, Object _nameSpace, Object _uid);
Object Processor_SetField(Object _self, Object _fieldName, Object _uid);
Object Processor_UniteField(Object _self, Object _destinationFieldName, Object _sourceFieldName);
Object Processor_UnDefineFieldInNamespace(Object _self, Object _fieldName, Object _locationType);
Object Processor_AddJobWithName(Object _self, Object _job, Object _jobName);
Object Processor_FinishThisJob(Object _self);
Object Processor_AddJobStage(Object _self, Object _jobStage, Object _jobStageName);
Object Processor_BlockStage(Object _self, Object _stageName);
Object Processor_UnBlockStage(Object _self, Object _stageName);
Object Processor_RemoveJobStage(Object _self, Object _jobStageName);
Object Processor_RemoveAllStages(Object _self);
Object Processor_AddMessageSlot(Object _self, Object _messageSlot, Object _messageSlotName);
Object Processor_BlockMessageSlot(Object _self, Object _messageSlotName);
Object Processor_UnBlockMessageSlot(Object _self, Object _messageSlotName);
Object Processor_RemoveMessageSlot(Object _self, Object _messageSlotName);
Object Processor_RemoveAllMessageSlots(Object _self);
Object Processor_AttachToStageMessageSlot(Object _self, Object _stageName, Object _messageName);
Object Processor_RemoveAllStagesAndMessageSlots(Object _self);
Object Processor_RemoveMessageInMessageSlot(Object _self, Object _messageSlotName);
Object Processor_RemoveAllMessagesOfCurrentStageForCurrentStage(Object _self);
Object Processor_RemoveAllMessagesOfCurrentStageForAllStages(Object _self);
Object Processor_RemoveAllMessagesOfAllOpenedStages(Object _self);
Object Processor_RemoveAllReceivedMessages(Object _self);
Object Processor_AddJobStageInJob(Object _self, Object _jobStage, Object _jobStageName, Object _jobName);
Object Processor_BlockStageInJob(Object _self, Object _stageName, Object _jobName);
Object Processor_UnBlockStageInJob(Object _self, Object _stageName, Object _jobName);
Object Processor_RemoveJobStageInJob(Object _self, Object _jobStageName, Object _jobName);
Object Processor_RemoveAllStagesInJob(Object _self, Object _jobName);
Object Processor_AddMessageSlotInJob(Object _self, Object _messageSlot, Object _messageSlotName, Object _jobName);
Object Processor_BlockMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName);
Object Processor_UnBlockMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName);
Object Processor_RemoveMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName);
Object Processor_RemoveAllMessageSlotsInJob(Object _self, Object _jobName);
Object Processor_AttachToStageMessageSlotInJob(Object _self, Object _stageName, Object _messageName, Object _jobName);
Object Processor_RemoveAllStagesAndMessageSlotsInJob(Object _self, Object _jobName);
Object Processor_RemoveMessageInMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName);
Object Processor_RemoveAllMessagesOfCurrentStageForCurrentStageInJob(Object _self, Object _jobName);
Object Processor_RemoveAllMessagesOfCurrentStageForAllStagesInJob(Object _self, Object _jobName);
Object Processor_RemoveAllMessagesOfAllOpenedStagesInJob(Object _self, Object _jobName);
Object Processor_RemoveAllReceivedMessagesInJob(Object _self, Object _jobName);
Object Processor_EntityFromNamedMessageField(Object _self, Object _messageName, Object _fieldName);
Object Processor_NamespaceNameToNamespace(Object _self, Object _locationType);
Object Processor_FieldNameToNamespaceName(Object _self, Object _fieldName);
Object Processor_FieldNameToSynonim(Object _self, Object _fieldName);
Object Processor_FieldNameToSynonimInJobObject(Object _self, Object _fieldName, Object _job, Object _object);
Object Processor_FieldNameToUID(Object _self, Object _fieldName);
Object Processor_EntityFromMessageField(Object _self, Object _fieldName, Object _messageSlotName);
Object Processor_SendMessage(Object _self, Object _message);
Object Processor_SendMessageToMessageField(Object _self, Object _message, Object _messageSlotName, Object _fieldName);
Object Processor_SendReplyForMessage(Object _self, Object _replyMessage, Object _messageSlotName);
Object Processor_InvokeMethodWithParameters(Object _self, Object _methodName, Object _parameters);
Object Processor_MessageConfirmsToParameterInJobObject(Object _self, Object _message, Object _parameter, Object _job, Object _object);
Object Processor_TryLinkMessageWithMessageSlotInJobObject(Object _self, Object _message, Object _messageSlot, Object _job, Object _object, Object _messageSlotName, Object _jobName);
Object Processor_ProcessMessageForObject(Object _self, Object _message, Object _object);
Object Processor_ProcessOneJobIfAny(Object _self);
Object Processor_ProcessUID(Object _self, Object _uid);
