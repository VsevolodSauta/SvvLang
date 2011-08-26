#include "internals/basics.h"
#include "internals/Number/library.h"
#include "internals/Logic/interface.h"
#include "internals/Comparison/interface.h"
#include "internals/SuperClass/interface.h"

Object Number_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Number));
	toReturn->gid = 15425740279749906432ull;
	Object_SetComparator(toReturn, &Number_Compare);
	Object_SetDestructor(toReturn, &Number_Destroy);
	Object_SetCloner(toReturn, &Number_Clone);
	Object_SetDeepCloner(toReturn, &Number_Clone);
	return toReturn;
}

Object Number_Clone(Object _self)
{
	Object toReturn = Number_Create();
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long;
	((Number) (toReturn->entity))->_div = ((Number) (_self->entity))->_div;
	return toReturn;
}

Object Number_Compare(Object _self, Object _number)
{
	long lcm = long_lcm(((Number) (_number->entity))->_div, ((Number) (_self->entity))->_div);
	long first = ((Number) (_self->entity))->_long * (lcm / ((Number) (_self->entity))->_div);
	long second = ((Number) (_number->entity))->_long * (lcm / ((Number) (_number->entity))->_div);
	
	if(first > second)
		return _greater;
	if(first < second)
		return _less;
	return _equal;
}

Object Number_Destroy(Object _self)
{
	return Object_Destroy(_self);
}

Object Number_NormalizeSign(Object _self)
{
	if(((Number) (_self->entity))->_div < 0)
	{
		((Number) (_self->entity))->_div = -((Number) (_self->entity))->_div;
		((Number) (_self->entity))->_long = -((Number) (_self->entity))->_long;
	}
	return _self;
}


Object Number_Add(Object _self, Object _number)
{
	long lcm = long_lcm(((Number) (_number->entity))->_div, ((Number) (_self->entity))->_div);
	long first = ((Number) (_self->entity))->_long * (lcm / ((Number) (_self->entity))->_div);
	long second = ((Number) (_number->entity))->_long * (lcm / ((Number) (_number->entity))->_div);
	long value = first + second;
	long gcd = long_gcd(lcm, value);

	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = value / gcd;
	((Number) (toReturn->entity))->_div = lcm / gcd;
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_Sub(Object _self, Object _number)
{
	long lcm = long_lcm(((Number) (_number->entity))->_div, ((Number) (_self->entity))->_div);
	long first = ((Number) (_self->entity))->_long * (lcm / ((Number) (_self->entity))->_div);
	long second = ((Number) (_number->entity))->_long * (lcm / ((Number) (_number->entity))->_div);
	long value = first - second;
	long gcd = long_gcd(lcm, value);

	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = value / gcd;
	((Number) (toReturn->entity))->_div = lcm / gcd;
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_Mul(Object _self, Object _number)
{
	long gcd1 = long_gcd(((Number) (_self->entity))->_long, ((Number) (_number->entity))->_div);
	long gcd2 = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_long);

	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = (((Number) (_self->entity))->_long / gcd1) * (((Number) (_number->entity))->_long / gcd2);
	((Number) (toReturn->entity))->_div = (((Number) (_self->entity))->_div / gcd2) * (((Number) (_number->entity))->_div / gcd1);
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_Div(Object _self, Object _number)
{
	long gcd1 = long_gcd(((Number) (_self->entity))->_long, ((Number) (_number->entity))->_long);
	long gcd2 = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_div);

	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = (((Number) (_self->entity))->_long / gcd1) * (((Number) (_number->entity))->_div / gcd2);
	((Number) (toReturn->entity))->_div = (((Number) (_self->entity))->_div / gcd2) * (((Number) (_number->entity))->_div / gcd1);
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_Power(Object _self, Object _number)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	long count = ((Number) (_number->entity))->_long;
	long num = 1;
	long den = 1;
	while(count--)
	{
		num *= ((Number) (_self->entity))->_long;
		den *= ((Number) (_self->entity))->_div;
	}
	((Number) (toReturn->entity))->_long = num;
	((Number) (toReturn->entity))->_div = den;
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_Mod(Object _self, Object _number)
{
	ASSERT_C ("First _numberument of Mod function is not an integer.", ((Number) (_self->entity))->_div == 1);
	ASSERT_C ("Second _numberument of Mod function is not an integer.", ((Number) (_number->entity))->_div == 1);
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long % ((Number) (_number->entity))->_long;
	((Number) (toReturn->entity))->_div = 1;
	ASSERT_C("Знаменатель равен нулю", ((Number) (toReturn->entity))->_div != 0)
	return Number_NormalizeSign(toReturn);
}

Object Number_AddInPlace(Object _self, Object _number)
{
	long gcd = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_div);
	long multiplier = ((Number) (_number->entity))->_div / gcd;
	((Number) (_self->entity))->_long *= multiplier;
	((Number) (_self->entity))->_long += ((Number) (_number->entity))->_long * (((Number) (_self->entity))->_div / gcd);
	((Number) (_self->entity))->_div *= multiplier;
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_SubInPlace(Object _self, Object _number)
{
	long gcd = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_div);
	long multiplier = ((Number) (_number->entity))->_div / gcd;
	((Number) (_self->entity))->_long *= multiplier;
	((Number) (_self->entity))->_long -= ((Number) (_number->entity))->_long * (((Number) (_self->entity))->_div / gcd);
	((Number) (_self->entity))->_div *= multiplier;
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_MulInPlace(Object _self, Object _number)
{
	long gcd1 = long_gcd(((Number) (_self->entity))->_long, ((Number) (_number->entity))->_div);
	long gcd2 = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_long);
	((Number) (_self->entity))->_long = (((Number) (_self->entity))->_long / gcd1) * (((Number) (_number->entity))->_long / gcd2);
	((Number) (_self->entity))->_div = (((Number) (_self->entity))->_div / gcd2) * (((Number) (_number->entity))->_div / gcd1);
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_DivInPlace(Object _self, Object _number)
{
	long gcd1 = long_gcd(((Number) (_self->entity))->_long, ((Number) (_number->entity))->_long);
	long gcd2 = long_gcd(((Number) (_self->entity))->_div, ((Number) (_number->entity))->_div);
	((Number) (_self->entity))->_long = (((Number) (_self->entity))->_long / gcd1) * (((Number) (_number->entity))->_div / gcd2);
	((Number) (_self->entity))->_div = (((Number) (_self->entity))->_div / gcd2) * (((Number) (_number->entity))->_long / gcd1);
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_ModInPlace(Object _self, Object _number)
{
	ASSERT_C ("First _numberument of Mod function is not an integer.", ((Number) (_self->entity))->_div == 1);
	ASSERT_C ("Second _numberument of Mod function is not an integer.", ((Number) (_number->entity))->_div == 1);
	((Number) (_self->entity))->_long %= ((Number) (_number->entity))->_long;
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_Inc(Object _self)
{
	((Number) (_self->entity))->_long += ((Number) (_self->entity))->_div;
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_Dec(Object _self)
{
	((Number) (_self->entity))->_long -= ((Number) (_self->entity))->_div;
	ASSERT_C("Знаменатель равен нулю", ((Number) (_self->entity))->_div != 0)
	return Number_NormalizeSign(_self);
}

Object Number_Min(Object _self, Object _number)
{
	Object comparation = Number_Compare(_self, _number);
	if(comparation == _less) {
		return Object_TempClone(_self);
	} else {
		return Object_TempClone(_number);
	}
}

Object Number_Max(Object _self, Object _number)
{
	Object comparation = Number_Compare(_self, _number);
	if(comparation != _less) {
		return Object_TempClone(_self);
	} else {
		return Object_TempClone(_number);
	}
}

Object Number_Abs(Object _self)
{
	if(((Number) (_self->entity))->_long > 0)
	{
		return Object_TempClone(_self);
	} else {
		return Number_Inv(_self);
	}
}

Object Number_Inv(Object _self)
{
	Object toReturn = Object_TempClone(_self);
	((Number) (toReturn->entity))->_long = -((Number) (toReturn->entity))->_long;
	return Number_NormalizeSign(toReturn);
}

Object Number_IsInteger(Object _self)
{
	return (((Number) (_self->entity))->_div == 1) ? _true : _false;
}

Object Number_IsOdd(Object _self)
{
	return ((((Number) (_self->entity))->_long & 1) && (((Number) (_self->entity))->_div == 1)) ? _true : _false;
}

Object Number_IsEven(Object _self)
{
	return (!(((Number) (_self->entity))->_long & 1) && (((Number) (_self->entity))->_div == 1)) ? _true : _false;
}

Object Number_Set(Object _self, Object _number)
{
	((Number) (_self->entity))->_long = ((Number) (_number->entity))->_long;
	((Number) (_self->entity))->_div = ((Number) (_number->entity))->_div;
	return Number_NormalizeSign(_self);
}

void Number_InitializeClass()
{
	Object _className = StringFactory_FromUTF8(_stringFactory, "Number", 6);
	
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Clone), StringFactory_FromUTF8(_stringFactory, "DeepClone", 9), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Clone), StringFactory_FromUTF8(_stringFactory, "Clone", 5), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Compare), StringFactory_FromUTF8(_stringFactory, "Compare", 7), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Destroy), StringFactory_FromUTF8(_stringFactory, "Destroy", 7), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Inc), StringFactory_FromUTF8(_stringFactory, "Inc", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Inc), StringFactory_FromUTF8(_stringFactory, "++", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Dec), StringFactory_FromUTF8(_stringFactory, "Dec", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Dec), StringFactory_FromUTF8(_stringFactory, "--", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Add), StringFactory_FromUTF8(_stringFactory, "Add", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Add), StringFactory_FromUTF8(_stringFactory, "+", 1), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Sub), StringFactory_FromUTF8(_stringFactory, "Sub", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Sub), StringFactory_FromUTF8(_stringFactory, "-", 1), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Mul), StringFactory_FromUTF8(_stringFactory, "Mul", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Mul), StringFactory_FromUTF8(_stringFactory, "*", 1), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Div), StringFactory_FromUTF8(_stringFactory, "Div", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Div), StringFactory_FromUTF8(_stringFactory, "/", 1), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Mod), StringFactory_FromUTF8(_stringFactory, "Mod", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Mod), StringFactory_FromUTF8(_stringFactory, "%", 1), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_AddInPlace), StringFactory_FromUTF8(_stringFactory, "AddInPlace", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_AddInPlace), StringFactory_FromUTF8(_stringFactory, "+=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_SubInPlace), StringFactory_FromUTF8(_stringFactory, "AddInPlace", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_SubInPlace), StringFactory_FromUTF8(_stringFactory, "-=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_MulInPlace), StringFactory_FromUTF8(_stringFactory, "AddInPlace", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_MulInPlace), StringFactory_FromUTF8(_stringFactory, "*=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_DivInPlace), StringFactory_FromUTF8(_stringFactory, "AddInPlace", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_DivInPlace), StringFactory_FromUTF8(_stringFactory, "/=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_ModInPlace), StringFactory_FromUTF8(_stringFactory, "AddInPlace", 10), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_ModInPlace), StringFactory_FromUTF8(_stringFactory, "%=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Min), StringFactory_FromUTF8(_stringFactory, "%=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Max), StringFactory_FromUTF8(_stringFactory, "%=", 2), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Abs), StringFactory_FromUTF8(_stringFactory, "Abs", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Inv), StringFactory_FromUTF8(_stringFactory, "Inv", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Power), StringFactory_FromUTF8(_stringFactory, "Power", 5), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_IsInteger), StringFactory_FromUTF8(_stringFactory, "IsInteger", 9), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_IsOdd), StringFactory_FromUTF8(_stringFactory, "IsOdd", 5), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_IsEven), StringFactory_FromUTF8(_stringFactory, "IsEven", 5), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &Number_Set), StringFactory_FromUTF8(_stringFactory, "Set", 3), _className);
}
