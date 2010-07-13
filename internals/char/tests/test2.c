#include "internals/basics.h"

int main(void)
{
	SvvInternalChar ch;
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 0x0053);
	TEST("Testing IsASCII", SvvInternalChar_IsASCII(ch) == 1);
	TEST("Testing IsLatin", SvvInternalChar_IsLatin(ch) == 1);
	TEST("Testing IsCyrillic", SvvInternalChar_IsCyrillic(ch) == 0);
	TEST("Testing IsCyrillic", SvvInternalChar_IsCyrillic(SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 0x0496)) == 1);
	ch = SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 0x0042);
	TEST("Testing IsDigit", SvvInternalChar_IsDigit(ch) == 0);
	TEST("Testing IsHexDigit", SvvInternalChar_IsHexDigit(ch) == 1);
	TEST("Testing IsBasicPunctOrSym", SvvInternalChar_IsBasicPunctOrSym(SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 0x21)));
	TEST("Testing IsBasicControl", SvvInternalChar_IsBasicControl(SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, 0x19)) == 1);
	return 0;
};
