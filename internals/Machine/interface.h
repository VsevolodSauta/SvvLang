typedef struct Machine {
	Object _placeHolder;
} *Machine;

Object Machine_Create(void);
Object Machine_Init(Object _self);
Object Machine_Destroy(Object _self);
Object Machine_Clone(Object _self);
Object Machine_Compare(Object _self, Object _machine);
