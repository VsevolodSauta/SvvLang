#pragma once

#include "internals/actions.h"

struct Object;

typedef struct Object* (*ObjectDestructor)(struct Object*);
typedef struct Object* (*ObjectComparator)(struct Object*, struct Object*);
typedef struct Object* (*ObjectCloner)(struct Object*);

typedef struct Object {
	long				gid;
	long				links;
	ObjectDestructor		destroy;
	ObjectComparator		compare;
	ObjectCloner			clone;
	void*				entity;
} *Object;

#define ENTITY(object, type) ((type) (object->entity))
#define SET_ENTITY(object, entit) (object->entity = (void*) (entit))

Creator(Object);
Action(Object, Destroy);
Action(Object, Retain);
Action(Object, Release);
Action(Object, Autorelease);

Action(Object, Compare, Object object);
Action(Object, Clone);
Action(Object, TempClone);

Action(Object, SetComparator, ObjectComparator);
Action(Object, SetCloner, ObjectCloner);
Action(Object, SetDestructor, ObjectDestructor);
