#include "internals/basics.h"
#include "internals/char/unicode.h"

#define TABLE(name, begin, end) UnicodeCodeTable name ##_Table = {begin, end}
#include "internals/char/tables.h"
#undef TABLE

inline static Routine(UnicodeCode, IsInTable, int, UnicodeCodeTable Table)
{
	return	(receiver >= Table[0]) && (receiver <= Table[1]);
};

Routine(UnicodeCode, IsASCII, int)
{
	return	UnicodeCode_IsInTable(receiver, ASCII_Table);
}

Routine(UnicodeCode, IsLatin, int)
{
	return	UnicodeCode_IsInTable(receiver, LatinUppercase_ASCII_Table) ||
		UnicodeCode_IsInTable(receiver, LatinLowercase_ASCII_Table) ||
		UnicodeCode_IsInTable(receiver, Letters_Latin_1_Table) ||
		UnicodeCode_IsInTable(receiver, Letters_Latin_2_Table) ||
		UnicodeCode_IsInTable(receiver, Letters_Latin_3_Table) ||
		UnicodeCode_IsInTable(receiver, European_Latin_1_Table) ||
		UnicodeCode_IsInTable(receiver, European_Latin_2_Table) ||
		UnicodeCode_IsInTable(receiver, Deprecated_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, NonEuropeanAndHistoric_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, African_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, Croatian_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, Pinyin_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, PhoneticAndHistoric_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, SlovenianAndCroatian_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, Livonian_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, Miscellanious_Latin_1_Table) ||
		UnicodeCode_IsInTable(receiver, Miscellanious_Latin_2_Table) ||
		UnicodeCode_IsInTable(receiver, Sinology_Latin_Table);
};

Routine(UnicodeCode, IsCyrillic, int)
{
	return	UnicodeCode_IsInTable(receiver, BasicRussian_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Extensions_Cyrillic_1_Table) ||
		UnicodeCode_IsInTable(receiver, Extensions_Cyrillic_2_Table) ||
		UnicodeCode_IsInTable(receiver, Extended_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Historic_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, HistoricMiscellaneous_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Nivkh_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Comi_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Khanty_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Mordvin_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Kurdish_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Aleut_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Chuvash_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Abkhaz_Cyrillic_Table) ||
		UnicodeCode_IsInTable(receiver, Azerbaijani_Cyrillic_Table);
};

Routine(UnicodeCode, IsDigit, int)
{
	return	UnicodeCode_IsInTable(receiver, Digits_ASCII_Table);
};

Routine(UnicodeCode, IsHexDigit, int)
{
	return	UnicodeCode_IsInTable(receiver, Digits_ASCII_Table) ||
		UnicodeCode_IsInTable(receiver, HexDigits_1_Table) ||
		UnicodeCode_IsInTable(receiver, HexDigits_2_Table);
};

Routine(UnicodeCode, IsBasicPunctOrSym, int)
{
	return	UnicodeCode_IsInTable(receiver, PunctAndSym_ASCII_1_Table) ||
		UnicodeCode_IsInTable(receiver, PunctAndSym_ASCII_2_Table) ||
		UnicodeCode_IsInTable(receiver, PunctAndSym_ASCII_3_Table) ||
		UnicodeCode_IsInTable(receiver, PunctAndSym_ASCII_4_Table) ||
		UnicodeCode_IsInTable(receiver, PunctAndSym_Latin_Table) ||
		UnicodeCode_IsInTable(receiver, MathSym_Latin_1_Table) ||
		UnicodeCode_IsInTable(receiver, MathSym_Latin_2_Table);
};

Routine(UnicodeCode, IsBasicControl, int)
{
	return	UnicodeCode_IsInTable(receiver, Control_C0_1_Table) || 
		UnicodeCode_IsInTable(receiver, Control_C0_2_Table) ||
		UnicodeCode_IsInTable(receiver, Control_C1_Table);
};

