TranslatorDebugger := Object clone

TranslatorDebugger blockDidBegin := method(
	Translator putNLevels(1)
	DestinationFile write("DPUSHS (\"#{Translator currentClassName}: #{Translator currentMethodName} begined.\")\n" interpolate)
)
