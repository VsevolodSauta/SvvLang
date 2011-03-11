typedef struct JSONParser {
	Object _error;
} *JSONParser;

Object JSONParser_Create(void);
Object JSONParser_Init(Object _self);
Object JSONParser_Compare(Object _self, Object _jsonParser);
Object JSONParser_Clone(Object _self);
Object JSONParser_DeepClone(Object _self);
Object JSONParser_Destroy(Object _self);
Object JSONParser_ParseString(Object _self, Object _iterator);
Object JSONParser_ParseObject(Object _self, Object _iterator);
Object JSONParser_ParseArray(Object _self, Object _iterator);
Object JSONParser_ParseValue(Object _self, Object _iterator);
Object JSONParser_ParseTrue(Object _self, Object _iterator);
Object JSONParser_ParseFalse(Object _self, Object _iterator);
Object JSONParser_ParseNull(Object _self, Object _iterator);
Object JSONParser_ParseNumber(Object _self, Object _iterator);
