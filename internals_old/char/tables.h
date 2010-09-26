// C0 and Basic Latin
TABLE(ASCII, 0x0000, 0x007F);
TABLE(HexDigits_1, 0x0041, 0x0046);
TABLE(HexDigits_2, 0x0061, 0x0066);

TABLE(Control_C0_1, 0x0000, 0x0020);
TABLE(PunctAndSym_ASCII_1, 0x0021, 0x002F);
TABLE(Digits_ASCII, 0x0030, 0x0039);
TABLE(PunctAndSym_ASCII_2, 0x003A, 0x0040);
TABLE(LatinUppercase_ASCII, 0x0041, 0x005A);
TABLE(PunctAndSym_ASCII_3, 0x005B, 0x0060);
TABLE(LatinLowercase_ASCII, 0x0061, 0x007A);
TABLE(PunctAndSym_ASCII_4, 0x007B, 0x007E);
TABLE(Control_C0_2, 0x007F, 0x007F);

// C1 and Latin-1 Supplement
TABLE(Control_C1, 0x0080, 0x009F);
TABLE(PunctAndSym_Latin, 0x00A0, 0x00BF);
TABLE(Letters_Latin_1, 0x00C0, 0x00D6);
TABLE(MathSym_Latin_1, 0x00D7, 0x00D7);
TABLE(Letters_Latin_2, 0x00D8, 0x00F6);
TABLE(MathSym_Latin_2, 0x00F7, 0x00F7);
TABLE(Letters_Latin_3, 0x00F9, 0x00FF);

// Latin Extended-A
TABLE(European_Latin_1, 0x0100, 0x0148);
TABLE(Deprecated_Latin, 0x0149, 0x0149);
TABLE(European_Latin_2, 0x014A, 0x01FF);

// Latin Extended-B
TABLE(NonEuropeanAndHistoric_Latin, 0x0180, 0x01BF);
TABLE(African_Latin, 0x01C0, 0x01C3);
TABLE(Croatian_Latin, 0x01C4, 0x01CC);
TABLE(Pinyin_Latin, 0x01CD, 0x01DC);
TABLE(PhoneticAndHistoric_Latin, 0x01DD, 0x01FF);
TABLE(SlovenianAndCroatian_Latin, 0x0200, 0x0217);
TABLE(Romanian_Latin, 0x0218, 0x021B);
TABLE(Miscellanious_Latin_1, 0x021C, 0x0229);
TABLE(Livonian_Latin, 0x022A, 0x0233);
TABLE(Sinology_Latin, 0x0234, 0x0236);
TABLE(Miscellanious_Latin_2, 0x0237, 0x024F);

// IPA Extension
TABLE(IPA, 0x0250, 0x02A8);
TABLE(IPA_Disordered, 0x02A9, 0x02AD);
TABLE(Sinology_IPA, 0x02AE, 0x02AF);

// Spacing Modifiers Letter
TABLE(SuperscriptLetter_Modifiers_Latin, 0x02B0, 0x02B8);
TABLE(Phonetic_Modifiers, 0x02B9, 0x02D7);
TABLE(Diacritic_Modifiers, 0x02D8, 0x02DD);
TABLE(IPA1989_Modifiers, 0x02DE, 0x02E4);
TABLE(Tone, 0x02E5, 0x02E9);
TABLE(ExtendedBopomofo_ToneMark, 0x02EA, 0x02EB);
TABLE(IPA_Modifiers, 0x02EC, 0x02ED);
TABLE(Other_Modifiers, 0x02EE, 0x02EE);
TABLE(UPA_Modifiers, 0x02EF, 0x02FF);

// Combinig Diacritical Marks
TABLE(Ordinary_Diacritics, 0x0300, 0x0333);
TABLE(Overstruck_Diacritics, 0x0334, 0x0338);
TABLE(Additional_Diacritics, 0x0339, 0x033F);
TABLE(Vietnamese_Diacritics, 0x0340, 0x0341);
TABLE(Greek_Diacritics, 0x0342, 0x0345);
TABLE(IPA_Diacritics, 0x0346, 0x034A);
TABLE(IPA_Disordered_Diacritics, 0x034B, 0x034E);
TABLE(GraphmeJoiner, 0x034F, 0x034F);
TABLE(UralicPhonetic_Diacritics, 0x0350, 0x0357);
TABLE(Miscellaneous_Diacritics, 0x0358, 0x035B);
TABLE(Double_Diacritics, 0x035C, 0x0362);
TABLE(Medieval_SuperscriptLetter_Diacritics, 0x0363, 0x036F);

// Greek and Coptic
TABLE(Archaic_Greek_1, 0x0370, 0x0373);
TABLE(NumeralSigns_Greek, 0x0374, 0x0375);
TABLE(Archaic_Greek_2, 0x0376, 0x0377);
TABLE(Reserved_Greek_1, 0x0378, 0x0379);
TABLE(IotaSubscript_Greek, 0x037A, 0x037A);
TABLE(EditoralLowercase_Greek, 0x037B, 0x037D);
TABLE(Punct_Greek_2, 0x037E, 0x037E);
TABLE(Reserved_Greek_2, 0x037F, 0x0383);
TABLE(SpacingAccentMarks_Greek, 0x0384, 0x0385);
TABLE(Letters_Greek_1, 0x0386, 0x0386);
TABLE(Punct_Greek_3, 0x0387, 0x0387);
TABLE(Letters_Greek_2, 0x0388, 0x03CE);
TABLE(VariantLetterforms_Greek_1, 0x03CF, 0x03D7);
TABLE(Archaic_Greek_3, 0x03D8, 0x03E1);
TABLE(Democrit_Coptic, 0x03E2, 0x03EF);
TABLE(VariantLetterforms_Greek_2, 0x03F0, 0x03F2);
TABLE(Additional_Greek, 0x03F3, 0x03F3);
TABLE(VariantLetterforms_Greek_3, 0x03F4, 0x03F6);
TABLE(AdditionalArchaicBactiran_Greek, 0x03F7, 0x03F8);
TABLE(VariantLetterforms_Greek_4, 0x03F9, 0x03F9);
TABLE(Archaic_Greek_4, 0x03FA, 0x03FB);
TABLE(Symbols_Greek, 0x03FC, 0x03FC);
TABLE(EditorialSymbols_Greek, 0x03FD, 0x03FF);

// Cyrillic
TABLE(Extensions_Cyrillic_1, 0x0400, 0x040F);
TABLE(BasicRussian_Cyrillic, 0x0410, 0x044F);
TABLE(Extensions_Cyrillic_2, 0x0450, 0x045F);
TABLE(Historic_Cyrillic, 0x0460, 0x0481);
TABLE(HistoricMiscellaneous_Cyrillic, 0x0482, 0x0489);
TABLE(Extended_Cyrillic, 0x048A, 0x04F9);
TABLE(Nivkh_Cyrillic, 0x04FA, 0x04FF);

// Cyrillic Supplements
TABLE(Comi_Cyrillic, 0x0500, 0x050F);
TABLE(Khanty_Cyrillic, 0x0510, 0x0513);
TABLE(Mordvin_Cyrillic, 0x0514, 0x0519);
TABLE(Kurdish_Cyrillic, 0x051A, 0x051D);
TABLE(Aleut_Cyrillic, 0x051E, 0x051F);
TABLE(Chuvash_Cyrillic, 0x0520, 0x0523);
TABLE(Abkhaz_Cyrillic, 0x0524, 0x0525);
TABLE(Azerbaijani_Cyrillic, 0x0526, 0x0527);
TABLE(Reserved_Cyrillic, 0x0528, 0x052F);

// Armenian
TABLE(Reserved_Armenian_1, 0x0530, 0x0530);
TABLE(Uppercase_Armenian, 0x0531, 0x0556);
TABLE(Reserved_Armenian_2, 0x0557, 0x0558);
TABLE(Modified_Armenian, 0x0559, 0x055F);
TABLE(Reserved_Armenian_3, 0x0560, 0x0560);
TABLE(Lowercase_Armenian, 0x0561, 0x0587);
TABLE(Reserved_Armenian_4, 0x0588, 0x0588);
TABLE(Punct_Armenian, 0x0589, 0x058A);
TABLE(Reserved_Armenian_5, 0x058B, 0x058F);

//TODO: Everything else...
