typedef struct ProcessorCommandSystem {
	Object _helperStack;
	Object _processorCodes;
	Object _processor;
} *ProcessorCommandSystem;

Object ProcessorCommandSystem_Create(void);
Object ProcessorCommandSystem_Clone(Object _self);
Object ProcessorCommandSystem_DeepClone(Object _self);
Object ProcessorCommandSystem_Compare(Object _self, Object _processorCommandSystem);
Object ProcessorCommandSystem_Destroy(Object _self);
Object ProcessorCommandSystem_SetProcessor(Object _self, Object _processor);
Object ProcessorCommandSystem_ContextSwitched(Object _self);
Object ProcessorCommandSystem_Init(Object _self);
Object ProcessorCommandSystem_Do(Object _self, Object _toDo);
Object ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(Object _self, Object _entityName, Object _toDo);
Object ProcessorCommandSystem_CodeDo(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeEntityFromMessageField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUIDFromField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddCurrentUIDToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddCurrentJobToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddCurrentJobStageToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddListToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddListMapToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveFromStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddEntityToListMap(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveEntityFromListMapByKey(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveEntityFromListMapByValue(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddEntityToList(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveEntityFromListByPosition(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveEntityFromListByValue(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddEntityToStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDuplicateTopInStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeSwapTopInStack(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeSendMessageToUID(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeSendMessageToField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeSendMessageToMessageField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeSendReplyForMessage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeInvokeMethod(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineActorMethod(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineJobMethod(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUnDefineMethod(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineLocalField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineJobField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineActorField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeDefineGlobalField(Object _self, Object _toDo);
Object ProcessorCommandSystem_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace);
Object ProcessorCommandSystem_CodeSetField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUniteField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUnDefineField(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddJob(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeFinishThisJob(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddJobStage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAddMessageSlot(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeBlockStage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUnBlockStage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeBlockMessageSlot(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeUnBlockMessageSlot(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveJobStage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveMessageSlot(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveMessageInMessageSlot(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForCurrentStage(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForAllStages(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllMessagesOfAllOpenedStages(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllReceivedMessages(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllStages(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllMessageSlots(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeRemoveAllStagesAndMessageSlots(Object _self, Object _toDo);
Object ProcessorCommandSystem_CodeAttachToStageMessageSlot(Object _self, Object _toDo);