typedef struct Console {
	Object _toRead;
	Object _toWrite;
} *Console;

Object Console_Create(void);
Object Console_Init(Object _self);
Object Console_WriteLnString(Object _self, Object _string);
Object Console_WriteString(Object _self, Object _string);
Object Console_WriteLnNumber(Object _self, Object _number);
Object Console_WriteHash(Object _self, Object _object);
Object Console_Clone(Object _self);
Object Console_DeepClone(Object _self);
Object Console_Compare(Object _self, Object _console);
Object Console_Destroy(Object _self);
