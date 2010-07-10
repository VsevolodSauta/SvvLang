#include "internals/actions.h"
#include "internals/char/unicode.h"

#define TABLE(name, begin, end) SvvInternalUnicodeCodeTable name ##_Table = {begin, end}
#include "internals/char/tables.h"
#undef TABLE

inline static SvvInternalAction(SvvInternalUnicodeCode, IsInTable, int, SvvInternalUnicodeCodeTable Table)
{
	return	(Receiver >= Table[0]) && (Receiver <= Table[1]);
};

SvvInternalAction(SvvInternalUnicodeCode, IsASCII, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, ASCII_Table);
}

SvvInternalAction(SvvInternalUnicodeCode, IsLatin, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, LatinUppercase_ASCII_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, LatinLowercase_ASCII_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Letters_Latin_1_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Letters_Latin_2_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Letters_Latin_3_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, European_Latin_1_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, European_Latin_2_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Deprecated_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, NonEuropeanAndHistoric_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, African_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Croatian_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Pinyin_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, PhoneticAndHistoric_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, SlovenianAndCroatian_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Livonian_Latin_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Miscellanious_Latin_1_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Miscellanious_Latin_2_Table) ||
 		SvvInternalUnicodeCode_IsInTable(Receiver, Sinology_Latin_Table);	
};

SvvInternalAction(SvvInternalUnicodeCode, IsCyrilic, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, BasicRussian_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Extensions_Cyrillic_1_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Extensions_Cyrillic_2_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Extended_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Historic_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, HistoricMiscellaneous_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Nivkh_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Comi_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Khanty_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Mordvin_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Kurdish_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Aleut_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Chuvash_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Abkhaz_Cyrillic_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Azerbaijani_Cyrillic_Table);
};

SvvInternalAction(SvvInternalUnicodeCode, IsDigit, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, Digits_ASCII_Table);
};

SvvInternalAction(SvvInternalUnicodeCode, IsHexDigit, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, Digits_ASCII_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, HexDigits_1_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, HexDigits_2_Table);
};

SvvInternalAction(SvvInternalUnicodeCode, IsBasicPunctOrSym, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, PunctAndSym_ASCII_1_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, PunctAndSym_ASCII_2_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, PunctAndSym_ASCII_3_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, PunctAndSym_ASCII_4_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, PunctAndSym_Latin_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, MathSym_Latin_1_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, MathSym_Latin_2_Table);
};

SvvInternalAction(SvvInternalUnicodeCode, IsBasicControl, int)
{
	return	SvvInternalUnicodeCode_IsInTable(Receiver, Control_C0_1_Table) || 
		SvvInternalUnicodeCode_IsInTable(Receiver, Control_C0_2_Table) ||
		SvvInternalUnicodeCode_IsInTable(Receiver, Control_C1_Table);
};

