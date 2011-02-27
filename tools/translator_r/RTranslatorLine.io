#!/usr/local/bin/io

RTranslatorLine := Object clone
RTranslatorLine with := method(number, line,
	toReturn := self clone
	toReturn rawLineNumber := number
	toReturn rawLine := line
	toReturn
)

RTranslatorLine indent := lazySlot(
	toReturn := 0
	rawLine foreach(a,
		if((list(32, 9, 10, 13) contains(a)) not,
			break,
			toReturn = toReturn + 1
		)
	)
	toReturn
)


RTranslatorLine tokens := lazySlot(
	listOfSeparators := list("(", ")", "{", "}", "[", "]")
	toReturn := List clone
	toReturn appendIfNotEmpty := method(string,
		stringClone := nil
		if(string beginsWithSeq("\"") and string endsWithSeq("\""),
			stringClone = string exclusiveSlice(1, string size - 1) asUCS2,
			stringClone = string asUCS2
		)
		string setSize(0)
		
		if(stringClone size != 0, self append(stringClone appendProto(RToken)))
	)
	parsingString := false
	parsingChar := false
	currentToken := "" asMutable
	escaped := false
	self rawLine foreach(position, charCode,
		char := charCode asCharacter
		if(parsingString,
			currentToken appendSeq(char)
			if(char == "\\",
				if(escaped,
					escaped = false,
					
					escaped = true
				)
				continue
			)
			if(char == "\"",
				if(escaped not,
					toReturn appendIfNotEmpty(currentToken)
					parsingString = false
					continue
				)
			)
			escaped = false
			continue
		)
		if(parsingChar,
			currentToken appendSeq(char)
			if(char == "\\",
				if(escaped,
					escaped = false,
					
					escaped = true
				)
				continue
			)
			if(char == "'",
				if(escaped not,
					toReturn appendIfNotEmpty(currentToken)
					parsingChar = false
					continue
				)
			)
			escaped = false
			continue
		)
		if(char == "\"", 
			toReturn appendIfNotEmpty(currentToken)
			currentToken appendSeq(char)
			parsingString = true
			continue
		)
		if(char == "'",
			toReturn appendIfNotEmpty(currentToken)
			currentToken appendSeq(char)
			parsingChar = true
			continue
		)
		if(listOfSeparators contains(char),
			toReturn appendIfNotEmpty(currentToken)
			toReturn append(char)
			continue
		)
		if((char == " ") or (char == "\t") or (char == "\n") or (char == "\r"),
			toReturn appendIfNotEmpty(currentToken)
			continue
		)
		currentToken appendSeq(char)
	)
	if((parsingChar not) and (parsingString not),
		toReturn appendIfNotEmpty(currentToken),
		RTranslatorError with("Line terminated while parsing string or character.", self)
	)
//	toReturn foreach(token, token appendProto(RToken))
	toReturn
)

