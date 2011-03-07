#include "internals/basics.h"
#include "internals/Console/imports.h"


Object Console_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Console: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Console));
	_self->gid =  2102628007026497536ull;
	Object_SetComparator(_self, &Console_Compare);
	Object_SetDestructor(_self, &Console_Destroy);
	Object_SetCloner(_self, &Console_Clone);
	Object_SetDeepCloner(_self, &Console_DeepClone);
	((Console) (_self->entity))->_toRead = _nil;
	((Console) (_self->entity))->_toWrite = _nil;
	_self = Console_Init(_self);
	DPOPS ("Console: Create ended.")
	return _self;
}

Object Console_Init(Object _self)
{
	DPUSHS ("Console: Init begined.")
	ASSERT_C ( "Console:Init --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	(((Console) (_self->entity))->_toRead) = File_Create();
	(((Console) (_self->entity))->_toWrite) = File_Create();
	Object toReturn = _self;
	DPOPS ("Console: Init ended.")
	return toReturn;
}

Object Console_WriteLnString(Object _self, Object _string)
{
	DPUSHS ("Console: WriteLnString begined.")
	ASSERT_C ( "Console:WriteLnString --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	ASSERT_C ( "Console:WriteLnString --- Checking for correct parameter type failed at parameter _string.", _string->gid ==  3732711262168886272ull || _string == _nil )
	File_WriteLnString((((Console) (_self->entity))->_toWrite), _string);
	Object toReturn = _self;
	DPOPS ("Console: WriteLnString ended.")
	return toReturn;
}

Object Console_WriteString(Object _self, Object _string)
{
	DPUSHS ("Console: WriteString begined.")
	ASSERT_C ( "Console:WriteString --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	ASSERT_C ( "Console:WriteString --- Checking for correct parameter type failed at parameter _string.", _string->gid ==  3732711262168886272ull || _string == _nil )
	File_WriteNakedString((((Console) (_self->entity))->_toWrite), _string);
	Object toReturn = _self;
	DPOPS ("Console: WriteString ended.")
	return toReturn;
}

Object Console_WriteLnNumber(Object _self, Object _number)
{
	DPUSHS ("Console: WriteLnNumber begined.")
	ASSERT_C ( "Console:WriteLnNumber --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	ASSERT_C ( "Console:WriteLnNumber --- Checking for correct parameter type failed at parameter _number.", _number->gid == 15425740279749906432ull || _number == _nil )
	File_WriteLnNumber((((Console) (_self->entity))->_toWrite), _number);
	Object toReturn = _self;
	DPOPS ("Console: WriteLnNumber ended.")
	return toReturn;
}

Object Console_WriteHash(Object _self, Object _object)
{
	DPUSHS ("Console: WriteHash begined.")
	ASSERT_C ( "Console:WriteHash --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	File_WriteLnNumber((((Console) (_self->entity))->_toWrite), Object_Hash(_object));
	Object toReturn = _self;
	DPOPS ("Console: WriteHash ended.")
	return toReturn;
}

Object Console_Clone(Object _self)
{
	DPUSHS ("Console: Clone begined.")
	ASSERT_C ( "Console:Clone --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	Object toReturn = _self;
	DPOPS ("Console: Clone ended.")
	return toReturn;
}

Object Console_DeepClone(Object _self)
{
	DPUSHS ("Console: DeepClone begined.")
	ASSERT_C ( "Console:DeepClone --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	Object toReturn = _self;
	DPOPS ("Console: DeepClone ended.")
	return toReturn;
}

Object Console_Compare(Object _self, Object _console)
{
	DPUSHS ("Console: Compare begined.")
	ASSERT_C ( "Console:Compare --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	ASSERT_C ( "Console:Compare --- Checking for correct parameter type failed at parameter _console.", _console->gid ==  2102628007026497536ull || _console == _nil )
	Object toReturn = _equal;
	DPOPS ("Console: Compare ended.")
	return toReturn;
}

Object Console_Destroy(Object _self)
{
	DPUSHS ("Console: Destroy begined.")
	ASSERT_C ( "Console:Destroy --- Checking for correct object type failed.", _self->gid ==  2102628007026497536ull )
	Object toReturn = _self;
	DPOPS ("Console: Destroy ended.")
	return toReturn;
}
