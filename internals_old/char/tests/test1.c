#include "internals/basics.h"

int main(void)
{
	SvvInternalChar ch;
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 3);
	TEST("Testing code of one byte length char", SvvInternalChar_GetCode(ch) == 1 << 3);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 7);
	TEST("Testing code of two byte length char", SvvInternalChar_GetCode(ch) == 1 << 7);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 12);
	TEST("Testing code of three byte length char", SvvInternalChar_GetCode(ch) == 1 << 12);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 19);
	TEST("Testing code of four byte length char", SvvInternalChar_GetCode(ch) == 1 << 19);
	return 0;
};
