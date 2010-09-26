#pragma once

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

Object Object_Create(void);
Object Object_Destroy(Object receiver);
Object Object_Retain(Object receiver);
Object Object_Release(Object receiver);
Object Object_Autorelease(Object receiver);
Object Object_Compare(Object receiver, Object object);
Object Object_Clone(Object receiver);
Object Object_TempClone(Object receiver);
Object Object_SetComparator(Object receiver, ObjectComparator);
Object Object_SetCloner(Object receiver, ObjectCloner);
Object Object_SetDestructor(Object receiver, ObjectDestructor);
