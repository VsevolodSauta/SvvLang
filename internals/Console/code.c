#include "internals/basics.h"
#include "internals/Console/imports.h"


Object Console_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Console));
	toReturn->gid =  2102628007026497536ull;
	Object_SetComparator(toReturn, &Console_Compare);
	Object_SetDestructor(toReturn, &Console_Destroy);
	Object_SetCloner(toReturn, &Console_Clone);
	Object_SetDeepCloner(toReturn, &Console_DeepClone);
	((Console) (toReturn->entity))->_toRead = _nil;
	((Console) (toReturn->entity))->_toWrite = _nil;
	toReturn = Console_Init(toReturn);
	return toReturn;
}

Object Console_Init(Object _self)
{
	(((Console) (_self->entity))->_toRead) = File_Create();
	(((Console) (_self->entity))->_toWrite) = File_Create();
	return _self;
}

Object Console_WriteLnString(Object _self, Object _string)
{
	File_WriteLnString((((Console) (_self->entity))->_toWrite), _string);
	return _self;
}

Object Console_WriteString(Object _self, Object _string)
{
	File_WriteNakedString((((Console) (_self->entity))->_toWrite), _string);
	return _self;
}

Object Console_WriteLnNumber(Object _self, Object _number)
{
	File_WriteLnNumber((((Console) (_self->entity))->_toWrite), _number);
	return _self;
}

Object Console_WriteHash(Object _self, Object _object)
{
	File_WriteLnNumber((((Console) (_self->entity))->_toWrite), Object_Hash(_object));
	return _self;
}

Object Console_Clone(Object _self)
{
	return _self;
}

Object Console_DeepClone(Object _self)
{
	return _self;
}

Object Console_Compare(Object _self, Object _console)
{
	return _equal;
}

Object Console_Destroy(Object _self)
{
	return _self;
}
