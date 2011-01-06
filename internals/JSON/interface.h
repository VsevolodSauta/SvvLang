typedef struct JSON {
	Object _null;
	Object _true;
	Object _false;
} *JSON;

Object JSON_Create(void);
Object JSON_Init(Object _self);
Object JSON_Compare(Object _self, Object _json);
Object JSON_Clone(Object _self);
Object JSON_Destroy(Object _self);
Object JSON_ParseString(Object _self, Object _iterator);
Object JSON_ParseObject(Object _self, Object _iterator);
Object JSON_ParseArray(Object _self, Object _iterator);
Object JSON_ParseValue(Object _self, Object _iterator);
Object JSON_ParseTrue(Object _self, Object _iterator);
Object JSON_ParseFalse(Object _self, Object _iterator);
Object JSON_ParseNull(Object _self, Object _iterator);
Object JSON_ParseNumber(Object _self, Object _iterator);
