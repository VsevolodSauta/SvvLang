typedef struct Char {
	Object _code;
} *Char;

Object Char_Create(void);
Object Char_Init(Object _self);
Object Char_Compare(Object _self, Object _char);
Object Char_Destroy(Object _self);
Object Char_Clone(Object _self);
Object Char_SetCode(Object _self, Object _code);
Object Char_GetCode(Object _self);
