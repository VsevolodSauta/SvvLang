typedef struct Runtime {
	Object _placeHolder;
} *Runtime;

Object Runtime_Create(void);
Object Runtime_Init(Object _self);
Object Runtime_Destroy(Object _self);
Object Runtime_Clone(Object _self);
Object Runtime_DeepClone(Object _self);
Object Runtime_Compare(Object _self, Object _runtime);
