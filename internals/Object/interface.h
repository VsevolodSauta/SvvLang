#pragma once

struct Object;

typedef struct Object* (*ObjectDestructor)(struct Object*);
typedef struct Object* (*ObjectComparator)(struct Object*, struct Object*);
typedef struct Object* (*ObjectCloner)(struct Object*);

typedef struct Object {
	long long int			gid;
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
Object Object_Hash(Object receiver);
Object Object_EmptyComparator(Object receiver, Object object);
Object Object_Is(Object receiver, Object object);

inline static Object Object_SetRetaining(Object *toSet, Object with)
{
	Object_Retain(with);
	Object_Release(*toSet);
	*toSet = with;
	return with;
}

inline static Object Object_SetCloning(Object *toSet, Object with)
{
	with = Object_Clone(with);
	Object_Release(*toSet);
	*toSet = with;
	return with;
}

inline static Object Object_SetReleasing(Object *toSet, Object with)
{
	Object_Release(*toSet);
	*toSet = with;
	return with;
}

