typedef struct Undestroyable {
	Object _placeHolder;
} *Undestroyable;

Object Undestroyable_Create(void);
Object Undestroyable_Destroy(Object _self);
Object Undestroyable_Clone(Object _self);
Object Undestroyable_DeepClone(Object _self);
Object Undestroyable_Compare(Object _self, Object _undestroyable);
