Keyword := Object clone
Keyword string := Sequence asMutable clone
Keyword process := nil

Keyword with := method(token,
	toReturn := Keyword clone
	toReturn string = token
	toReturn
)

Keyword process := method(line,
	doString("self #{string}Process(line)" interpolate)
)

Keyword returnProcess := method(line,
	line toNextToken
	DestinationFile write("return #{line getActor(false) actorName};" interpolate)
)

Keyword loopProcess := method(line,
	DestinationFile write("while(1)")
)

Keyword elseProcess := method(line,
	DestinationFile write("else")
)

Keyword whileProcess := method(line,
	line toNextToken
	DestinationFile write("while(#{line getCondition})" interpolate)
)

Keyword ifProcess := method(line,
	line toNextToken
	DestinationFile write("if(#{line getCondition})" interpolate)
)

Keyword continueProcess := method(line,
	DestinationFile write("continue;")
)

Keyword breakProcess := method(line,
	DestinationFile write("break;")
)

Keyword defProcess := method(line,
	line toNextToken
	DestinationFile write("Object def = #{line getActor(false) actorName};" interpolate)
	BlockDelegatesHandling beforeBlockEnds(KeywordDefHandler, 5)
)

Keyword CProcess := method(line,
	line tokens foreach(index, token,
		if(index == 0, continue)
		DestinationFile write(token .. " ")
	)
)

KeywordDefHandler := Object clone

KeywordDefHandler blockWillEnd := method(
	Translator putNLevels(1)
	DestinationFile write("return def;\n")
	Translator putCurrentLevels(-1)
)
