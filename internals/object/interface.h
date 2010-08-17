#pragma once

#include "internals/actions.h"

/*
	Основная идея использования этой сущности:
	Ее можно использовать внутри других internal объектов.
	Ее достаточно просто использовать внутри internal объектов.
	
	------------------------------------------------------------
	Реализация:
	1) Она непрозрачная.
	
	2) Есть метод destroy. 
	Он принимает void*, а возвращает void. 
	Он деинициализирует и уничтожает объект.
	
	3) Есть счетчик ссылок на объект links.
	При достижении счетчиком нуля вызывается метод destroy. 
	Есть методы управления счетчиком: Retain, Release, Autorelease.
	retain увеличивает значение счетчика на 1.
	release уменьшает значение счетчика на 1.
	autorelease регестрирует объект в ближайшем AutoreleasePool.
	
	4) При вызове Drain у AutoreleasePool он вызывает Release у всех объектов, 
	в нем зарегестрированных, согласно кратностям их регистрации.

	5) Правило освобождения: кто создал объект, тот вызывает в нем Release.
	Кто не может в нем вызвать Release, тот вызывает Autorelease еще при создании.
*/

struct SvvInternalObject;

typedef void (*SvvInternalObjectDestructor)(struct SvvInternalObject*);
typedef struct SvvInternalObject* (*SvvInternalObjectComparator)(struct SvvInternalObject*, struct SvvInternalObject*);

typedef struct SvvInternalObject {
	long				gid;
	long				links;
	SvvInternalObjectDestructor	destroy;
	SvvInternalObjectComparator	compare;
	void*				entity;
} *SvvInternalObject;

#define GET_ENTITY(object, type) ((type) (object->entity))
#define SET_ENTITY(object, entit) (object->entity = (void*) (entit))

SvvInternalAction(SvvInternalObject, Compare, SvvInternalObject object);
SvvInternalCreator(SvvInternalObject);
void SvvInternalObject_Destroy(SvvInternalObject Receiver);
SvvInternalAction(SvvInternalObject, Retain);
SvvInternalAction(SvvInternalObject, Release);
SvvInternalAction(SvvInternalObject, Autorelease);
