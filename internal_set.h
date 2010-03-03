#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"

/*
     Структура множества.
        Множество прежставляет собой двоичное поисковое дерево.
        Вершины дерева делятся на 2 категории: инициализированные и неинициализированные.
        У любой инициализированной вершины всегда есть правый и левый сыновья.
        В инициализированной вершине хранится реальное значение, имеющееся в множестве.
*/

typedef struct SvvInternalSetNode {
	struct SvvInternalSetNode*	left;
	struct SvvInternalSetNode*	right;
	struct SvvInternalSetNode*	parent;
	SvvInternalObject		data;
	int				flags;
} *SvvInternalSetNode;

typedef struct SvvInternalSet {
	SvvInternalSetNode		root;
} *SvvInternalSet;

typedef struct SvvInternalSetIterator {
	SvvInternalStack		path;
	SvvInternalSetNode		node;
} *SvvInternalSetIterator;

SvvInternalCreator(SvvInternalSetNode);
SvvInternalAction(SvvInternalSetNode, Init, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSetNode, GetNodeForData, SvvInternalSetNode, SvvInternalObject Object);
SvvInternalAction(SvvInternalSetNode, Remove, void);
SvvInternalAction(SvvInternalSetNode, CleanSubTree, void);
SvvInternalAction(SvvInternalSetNode, DeInit, void);
SvvInternalAction(SvvInternalSetNode, Inited, int);
SvvInternalAction(SvvInternalSetNode, Destroy, void);
SvvInternalAction(SvvInternalSetNode, GetData, SvvInternalObject);

SvvInternalCreator(SvvInternalSetIterator);
SvvInternalAction(SvvInternalSetIterator, GetNext, void);
SvvInternalAction(SvvInternalSetIterator, EndReached, int);
SvvInternalAction(SvvInternalSetIterator, GetData, SvvInternalObject);
SvvInternalAction(SvvInternalSetIterator, Destroy, void);
SvvInternalAction(SvvInternalSetIterator, Clone, SvvInternalSetIterator);
SvvInternalAction(SvvInternalSetIterator, AddCurrentNodeChildren, void);

SvvInternalCreator(SvvInternalSet);
SvvInternalAction(SvvInternalSet, Destroy, void);
SvvInternalAction(SvvInternalSet, Add, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Remove, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Clean, void);
SvvInternalAction(SvvInternalSet, Exists, int, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalSet, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalSet, GetIterator, SvvInternalSetIterator);
