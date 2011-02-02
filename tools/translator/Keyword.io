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
	Translator putCurrentLevels
	DestinationFile write("Object toReturn = #{line getActor actorName};\n" interpolate)
	Translator putCurrentLevels
	DestinationFile write("DPOPS (\"#{Translator currentClassName}: #{Translator currentMethodName} ended.\")\n" interpolate)
	"return toReturn;" interpolate
)

Keyword loopProcess := method(line,
	"while(1)"
)

Keyword elseProcess := method(line,
	"else"
)

Keyword elifProcess := method(line,
	"else #{ifProcess(line)}" interpolate
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
	"Object def = #{line getActor actorName};" interpolate
)

Keyword CProcess := method(line,
	toReturn := "" asMutable
	line tokens foreach(index, token,
		if(index == 0, continue)
		toReturn appendSeq(token, " ")
	)
	toReturn
)

Keyword DEBUG_MSGProcess := method(line,
	toReturn := "DMSGS" asMutable
	line tokens foreach(index, token,
		if(index == 0, continue)
		toReturn appendSeq(token, " ")
	)
	toReturn
)

Keyword DEBUG_PUSHProcess := method(line,
	toReturn := "DPUSHS " asMutable
	line tokens foreach(index, token,
		if(index == 0, continue)
		toReturn appendSeq(token, " ")
	)
	toReturn
)

Keyword DEBUG_POPProcess := method(line,
	toReturn := "DPOPS " asMutable
	line tokens foreach(index, token,
		if(index == 0, continue)
		toReturn appendSeq(token, " ")
	)
	toReturn
)

Keyword assertProcess := method(line,
	toReturn := "ASSERT_Q ( " asMutable
	line toNextToken
	toReturn appendSeq(line currentToken)
	line toNextToken
	toReturn appendSeq(", ", (line getActor actorName), " )")
	toReturn
)

KeywordDefHandler := Object clone

KeywordDefHandler blockWillEnd := method(
	Translator putNLevels(1)
	DestinationFile write("DPOPS (\"#{Translator currentClassName}: #{Translator currentMethodName} ended.\")\n" interpolate)
	Translator putCurrentLevels
	DestinationFile write("return def;\n")
	Translator putCurrentLevels(-1)
)
