typedef struct UIDGenerator {
	Object _currentUID;
} *UIDGenerator;

Object UIDGenerator_Create(void);
Object UIDGenerator_Init(Object _self);
Object UIDGenerator_Clone(Object _self);
Object UIDGenerator_DeepClone(Object _self);
Object UIDGenerator_Destroy(Object _self);
Object UIDGenerator_Compare(Object _self, Object _uidGenerator);
Object UIDGenerator_GenerateUID(Object _self);
