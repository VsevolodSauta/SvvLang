typedef struct MapIterator {
	Object _map;
	Object _keysIterator;
	Object _valuesIterator;
} *MapIterator;

Object MapIterator_Create(void);
Object MapIterator_SetMap(Object _self, Object _map);
Object MapIterator_ToBegin(Object _self);
Object MapIterator_ToEnd(Object _self);
Object MapIterator_Next(Object _self);
Object MapIterator_Prev(Object _self);
Object MapIterator_ThisEnd(Object _self);
Object MapIterator_ThisBegin(Object _self);
Object MapIterator_PrevBegin(Object _self);
Object MapIterator_NextEnd(Object _self);
Object MapIterator_ThisKey(Object _self);
Object MapIterator_NextKey(Object _self);
Object MapIterator_PrevKey(Object _self);
Object MapIterator_ThisValue(Object _self);
Object MapIterator_NextValue(Object _self);
Object MapIterator_PrevValue(Object _self);
Object MapIterator_Compare(Object _self, Object _mapIterator);
Object MapIterator_Clone(Object _self);
Object MapIterator_DeepClone(Object _self);
Object MapIterator_Destroy(Object _self);
