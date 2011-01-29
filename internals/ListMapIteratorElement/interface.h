typedef struct ListMapIteratorElement {
	Object _node;
	Object _iterator;
	Object _nextExists;
	Object _prevExists;
} *ListMapIteratorElement;

Object ListMapIteratorElement_Create(void);
Object ListMapIteratorElement_AdvancingValue(Object _self, Object _prevElement);
Object ListMapIteratorElement_ReturningValue(Object _self, Object _prevElement);
Object ListMapIteratorElement_Clone(Object _self);
Object ListMapIteratorElement_DeepClone(Object _self);
Object ListMapIteratorElement_Compare(Object _self, Object _element);
Object ListMapIteratorElement_Destroy(Object _self);
