typedef struct MachineScheduler {
	Object _placeholder;
} *MachineScheduler;

Object MachineScheduler_Create(void);
Object MachineScheduler_GetNextObject(Object _self);
Object MachineScheduler_Destroy(Object _self);
Object MachineScheduler_Clone(Object _self);
Object MachineScheduler_Compare(Object _self, Object _scheduler);
