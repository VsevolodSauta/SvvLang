TranslatorDebugger := Object clone

TranslatorDebugger blockDidBegin := method(
	Translator putNLevels(1)
	DestinationFile write("DPUSHS (\"#{Translator currentClassName}: #{Translator currentMethodName} begined.\")\n" interpolate)
	Translator putNLevels(1)
	DestinationFile write("ASSERT_C ( \"Checking for correct object type\", _self->gid == #{TableOfSymbols getClassId(Translator currentClassName)}l )\n" interpolate)
)
