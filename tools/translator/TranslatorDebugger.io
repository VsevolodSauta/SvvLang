TranslatorDebugger := Object clone

TranslatorDebugger blockDidBegin := method(
	Translator putNLevels(1)
	DestinationFile write("DPUSHS (\"#{Translator currentClassName}: #{Translator currentMethodName} begined.\")\n" interpolate)
	Translator putNLevels(1)
	DestinationFile write("ASSERT_C ( \"#{Translator currentClassName}:#{Translator currentMethodName} --- Checking for correct object type failed.\", _self->gid == #{TableOfSymbols getClassId(Translator currentClassName)} )\n" interpolate)
)
