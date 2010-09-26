#include "internals/basics.h"
#include "internals/char/interface.h"
#include "internals/char_factory/interface.h"

int main(void)
{
	SvvInternalChar ch;
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 3);
	TEST("Testing length of one byte length char", SvvInternalChar_GetLengthInBytes(ch) == 1);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 7);
	TEST("Testing length of two byte length char", SvvInternalChar_GetLengthInBytes(ch) == 2);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 12);
	TEST("Testing length of three byte length char", SvvInternalChar_GetLengthInBytes(ch) == 3);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 1 << 19);
	TEST("Testing length of four byte length char", SvvInternalChar_GetLengthInBytes(ch) == 4);
	return 0;
};
