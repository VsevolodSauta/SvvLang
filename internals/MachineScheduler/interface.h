typedef struct MachineScheduler {
	Object _queue;
} *MachineScheduler;

Object MachineScheduler_Create(void);
Object MachineScheduler_Init(Object _self);
Object MachineScheduler_GetNextUID(Object _self);
Object MachineScheduler_ScheduleUID(Object _self, Object _uid);
Object MachineScheduler_Destroy(Object _self);
Object MachineScheduler_DeepClone(Object _self);
Object MachineScheduler_Clone(Object _self);
Object MachineScheduler_Compare(Object _self, Object _scheduler);
