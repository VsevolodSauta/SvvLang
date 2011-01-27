typedef struct Map {
	Object _keys;
	Object _values;
} *Map;

Object Map_Create(void);
Object Map_Init(Object _self);
Object Map_Destroy(Object _self);
Object Map_Clone(Object _self);
Object Map_DeepClone(Object _self);
Object Map_Compare(Object _self, Object _map);
Object Map_Empty(Object _self);
Object Map_Size(Object _self);
Object Map_Add(Object _self, Object _key, Object _value);
Object Map_RemoveKey(Object _self, Object _key);
Object Map_RemoveKeyConfirming(Object _self, Object _key);
Object Map_ContainsKey(Object _self, Object _key);
Object Map_GetValueForKey(Object _self, Object _key);
