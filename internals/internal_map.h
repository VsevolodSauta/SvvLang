#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"

/*
     Структура карты.
        Карта прежставляет собой двоичное поисковое дерево.
        Вершины дерева делятся на 2 категории: инициализированные и неинициализированные.
        У любой инициализированной вершины всегда есть правый и левый сыновья.
        В инициализированной вершине хранится реальное значение, имеющееся в множестве.
*/

typedef struct SvvInternalMapNode {
	struct SvvInternalMapNode*	left;
	struct SvvInternalMapNode*	right;
	struct SvvInternalMapNode*	parent;
	SvvInternalObject		key;
	SvvInternalObject		value;
	int				flags;
} *SvvInternalMapNode;

typedef struct SvvInternalMap {
	SvvInternalMapNode		root;
	int				capacity;
} *SvvInternalMap;

typedef struct SvvInternalMapIterator {
	SvvInternalStack		path;
	SvvInternalMapNode		node;
} *SvvInternalMapIterator;

SvvInternalCreator(SvvInternalMapNode);
SvvInternalAction(SvvInternalMapNode, Init, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalMapNode, GetNodeForKey, SvvInternalMapNode, SvvInternalObject Key);
SvvInternalAction(SvvInternalMapNode, Remove, void);
SvvInternalAction(SvvInternalMapNode, CleanSubTree, void);
SvvInternalAction(SvvInternalMapNode, DeInit, void);
SvvInternalAction(SvvInternalMapNode, Inited, int);
SvvInternalAction(SvvInternalMapNode, Destroy, void);
SvvInternalAction(SvvInternalMapNode, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalMapNode, GetValue, SvvInternalObject);

SvvInternalCreator(SvvInternalMapIterator);
SvvInternalAction(SvvInternalMapIterator, GetNext, void);
SvvInternalAction(SvvInternalMapIterator, EndReached, int);
SvvInternalAction(SvvInternalMapIterator, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalMapIterator, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalMapIterator, Destroy, void);
SvvInternalAction(SvvInternalMapIterator, Clone, SvvInternalMapIterator);
SvvInternalAction(SvvInternalMapIterator, AddCurrentNodeChildren, void);
SvvInternalAction(SvvInternalMapIterator, GetNode, SvvInternalMapNode);

SvvInternalCreator(SvvInternalMap);
SvvInternalAction(SvvInternalMap, Destroy, void);
SvvInternalAction(SvvInternalMap, Add, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalMap, RemoveKey, void, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, RemoveValue, void, SvvInternalObject Value);
SvvInternalAction(SvvInternalMap, Clean, void);
SvvInternalAction(SvvInternalMap, ExistsKey, int, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, GetValue, SvvInternalObject, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, GetList, SvvInternalList);
SvvInternalAction(SvvInternalMap, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalMap, GetIterator, SvvInternalMapIterator);
SvvInternalAction(SvvInternalMap, GetCapacity, int);
