#!/usr/local/bin/io

BlockDelegatesHandling := Object clone

BlockDelegatesHandling delegatesBeforeEachBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesBeforeOneBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesAfterOneBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesAfterEachBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesBeforeBlockEnds := List clone
BlockDelegatesHandling delegatesAfterBlockEnds := List clone

BlockDelegatesHandling beforeEachBlockBegins := method(delegate, prio,
	delegatesBeforeEachBlockBegins last at(prio) push(delegate)
)

BlockDelegatesHandling beforeOneBlockBegins := method(delegate, prio,
	delegatesBeforeOneBlockBegins last at(prio) push(delegate)
)

BlockDelegatesHandling beforeBlockEnds := method(delegate, prio,
	delegatesBeforeBlockEnds last at(prio) push(delegate)
)

BlockDelegatesHandling afterOneBlockBegins := method(delegate, prio,
	delegatesAfterEachBlockBegins last at(prio) push(delegate)
)

BlockDelegatesHandling afterEachBlockBegins := method(delegate, prio,
	delegatesAfterEachBlockBegins last at(prio) push(delegate)
)

BlockDelegatesHandling afterBlockEnds := method(delegate, prio,
	delegatesAfterBlockEnds last at(prio) push(delegate)
)

BlockDelegatesHandling handleWithListAndName := method(delegatesList, name, remove,
	if(remove,
		delegatesList pop reverseForeach(list,
			list foreach(delegate,
				delegate performWithArgList(name, list())
			)
		),
		
		delegatesList last reverseForeach(list,
			list foreach(delegate,
				delegate performWithArgList(name, list())
			)
		)
	)
)

BlockDelegatesHandling blockWillBegin := method(
	delegatesBeforeBlockEnds push(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterBlockEnds push(list(list(), list(), list(), list(), list(), list()))
	handleWithListAndName(delegatesBeforeOneBlockBegins, "blockWillBegin", true)
	delegatesBeforeOneBlockBegins push(list(list(), list(), list(), list(), list(), list()))
	handleWithListAndName(delegatesBeforeEachBlockBegins, "blockWillBegin", false)
	delegatesBeforeEachBlockBegins push(list(list(), list(), list(), list(), list(), list()))
	if(Translator previousLevel != 0,
		TableOfSymbols pushFrame
	)
)

BlockDelegatesHandling blockDidBegin := method(
	handleWithListAndName(delegatesAfterOneBlockBegins, "blockDidBegin", true)
	delegatesAfterOneBlockBegins push(list(list(), list(), list(), list(), list(), list()))
	handleWithListAndName(delegatesAfterEachBlockBegins, "blockDidBegin", false)
	delegatesAfterEachBlockBegins push(list(list(), list(), list(), list(), list(), list()))
)

BlockDelegatesHandling blockWillEnd := method(
	delegatesBeforeOneBlockBegins pop
	delegatesBeforeEachBlockBegins pop
	delegatesAfterOneBlockBegins pop
	delegatesAfterEachBlockBegins pop
	handleWithListAndName(delegatesBeforeBlockEnds, "blockWillEnd", true)
	delegatesBeforeOneBlockBegins push(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterOneBlockBegins push(list(list(), list(), list(), list(), list(), list()))
)

BlockDelegatesHandling blockDidEnd := method(
	TableOfSymbols popFrame
	handleWithListAndName(delegatesAfterBlockEnds, "blockDidEnd", true)
)
