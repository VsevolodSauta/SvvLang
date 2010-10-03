#!/usr/local/bin/io

TranslatorWarning := Object clone
TranslatorWarning with := method(line, string,
	if(line isNil,
		if(Translator line isNil,
			"Warning: #{string}" interpolate println,
			
			"Warning: #{Translator line number}: #{string}" interpolate println
		),
		
		"Warning: #{line number}: #{string}" interpolate println
	)
)
