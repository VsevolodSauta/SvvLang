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
	"return #{line getActor(false) actorName};" interpolate
)

Keyword loopProcess := method(line,
	"while(1)"
)

Keyword elseProcess := method(line,
	"else"
)

Keyword whileProcess := method(line,
	line toNextToken
	"while(#{line getCondition})" interpolate
)

Keyword ifProcess := method(line,
	line toNextToken
	"if(#{line getCondition})" interpolate
)

Keyword continueProcess := method(line,
	"continue;"
)

Keyword breakProcess := method(line,
	"break;"
)

Keyword defProcess := method(line,
	line toNextToken
	BlockDelegatesHandling beforeBlockEnds(KeywordDefHandler, 5)
	"Object def = #{line getActor(false) actorName};" interpolate
)

Keyword CProcess := method(line,
	toReturn := "" asMutable
	line tokens foreach(index, token,
		if(index == 0, continue)
		toReturn appendSeq(token, " ")
	)
	toReturn
)

KeywordDefHandler := Object clone

KeywordDefHandler blockWillEnd := method(
	Translator putNLevels(1)
	DestinationFile write("return def;\n")
	Translator putCurrentLevels(-1)
)
