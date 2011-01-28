#!/usr/local/bin/io

BlockDelegatesHandling := Object clone

BlockDelegatesHandling delegatesBeforeEachBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesBeforeOneBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesAfterOneBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesAfterEachBlockBegins := list(list(list(), list(), list(), list(), list(), list()))
BlockDelegatesHandling delegatesBeforeBlockEnds := List clone
BlockDelegatesHandling delegatesAfterBlockEnds := List clone

BlockDelegatesHandling beforeEachBlockBegins := method(delegate, prio,
	delegatesBeforeEachBlockBegins first at(prio) push(delegate)
)

BlockDelegatesHandling beforeOneBlockBegins := method(delegate, prio,
	delegatesBeforeOneBlockBegins first at(prio) push(delegate)
)

BlockDelegatesHandling beforeBlockEnds := method(delegate, prio,
	delegatesBeforeBlockEnds first at(prio) push(delegate)
)

BlockDelegatesHandling afterOneBlockBegins := method(delegate, prio,
	delegatesAfterEachBlockBegins first at(prio) push(delegate)
)

BlockDelegatesHandling afterEachBlockBegins := method(delegate, prio,
	delegatesAfterEachBlockBegins first at(prio) push(delegate)
)

BlockDelegatesHandling afterBlockEnds := method(delegate, prio,
	delegatesAfterBlockEnds first at(prio) push(delegate)
)

BlockDelegatesHandling poppingHandleWithListAndName := method(delegatesList, name, offset,
	delegatesList removeAt(offset) reverseForeach(list,
		list foreach(delegate,
			delegate performWithArgList(name, list())
		)
	)
)

BlockDelegatesHandling peekingHandleWithListAndName := method(delegatesList, name, offset,
	delegatesList at(offset) reverseForeach(list,
		list foreach(delegate,
			delegate performWithArgList(name, list())
		)
	)
)

BlockDelegatesHandling blockWillBegin := method(
	delegatesBeforeBlockEnds prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterBlockEnds prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesBeforeOneBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesBeforeEachBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterOneBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterEachBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	poppingHandleWithListAndName(delegatesBeforeOneBlockBegins, "blockWillBegin", 1)
	peekingHandleWithListAndName(delegatesBeforeEachBlockBegins, "blockWillBegin", 1)
)

BlockDelegatesHandling blockDidBegin := method(
	poppingHandleWithListAndName(delegatesAfterOneBlockBegins, "blockDidBegin", 1)
	peekingHandleWithListAndName(delegatesAfterEachBlockBegins, "blockDidBegin", 1)
)

BlockDelegatesHandling blockWillEnd := method(
	delegatesBeforeOneBlockBegins removeFirst
	delegatesBeforeEachBlockBegins removeFirst
	delegatesAfterOneBlockBegins removeFirst
	delegatesAfterEachBlockBegins removeFirst
	delegatesBeforeOneBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	delegatesAfterOneBlockBegins prepend(list(list(), list(), list(), list(), list(), list()))
	poppingHandleWithListAndName(delegatesBeforeBlockEnds, "blockWillEnd", 0)
)

BlockDelegatesHandling blockDidEnd := method(
	poppingHandleWithListAndName(delegatesAfterBlockEnds, "blockDidEnd", 0)
)
