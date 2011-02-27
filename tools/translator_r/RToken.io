#!/usr/local/bin/io

RToken := Sequence clone
RToken isJob := method(
	beginsWithSeq("+") and endsWithSeq("+")
)

RToken isMessageField := method(
	beginsWithSeq("_")
)

RToken isField := method(
	beginsWithSeq("*")
)

RToken name := method(
	if(isJob,
		return exclusiveSlice(1, size - 1)
	)
	if(isMessageField or isField,
		return exclusiveSlice(1, size)
	)
)

