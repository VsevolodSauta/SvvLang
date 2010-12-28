typedef struct Token {
	Object _typeQualifier;
	Object _entity;
} *Token;

Object Token_Create(void);
Object Token_Init(Object _self);
Object Token_Compare(Object _self, Object _token);
Object Token_Destroy(Object _self);
Object Token_HasNil(Object _self);
Object Token_HasNumber(Object _self);
Object Token_HasString(Object _self);
Object Token_HasObject(Object _self);
Object Token_SetNil(Object _self);
Object Token_SetNumber(Object _self, Object _number);
Object Token_SetString(Object _self, Object _string);
Object Token_SetObject(Object _self, Object _object);
