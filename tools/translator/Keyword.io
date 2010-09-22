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
	DestinationFile write("return #{line getActor actorName};" interpolate)
)

Keyword whileProcess := method(line,
	line toNextToken
	DestinationFile write("while(#{line getCondition})" interpolate)
)

Keyword ifProcess := method(line,
	line toNextToken
	DestinationFile write("if(#{line getCondition})" interpolate)
)