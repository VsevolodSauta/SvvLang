#!/usr/local/bin/io

TranslatorError := Object clone
TranslatorError with := method(line, string,
	if(line isNil,
		if(Translator line isNil,
			"Error: #{string}" interpolate println,
			
			"Error: #{Translator line number}: #{string}" interpolate println
		),
		
		"Error: #{line number}: #{string}" interpolate println
	)
	System exit(1)
)
