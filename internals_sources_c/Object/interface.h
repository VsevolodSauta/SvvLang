#pragma once

struct Object;

typedef struct Object* (*ObjectDestructor)(struct Object*);
typedef struct Object* (*ObjectComparator)(struct Object*, struct Object*);
typedef struct Object* (*ObjectCloner)(struct Object*);

typedef struct Object {
	void*				entity;
	long				gid;
	long				links;
	ObjectDestructor		destroy;
	ObjectComparator		compare;
	ObjectCloner			clone;
	ObjectCloner			deepClone;
	struct Object*			classInvocationMap;
} *Object;

Object Object_Create(void);
Object Object_Destroy(Object _self);
Object Object_Retain(Object _self);
Object Object_Release(Object _self);
Object Object_Autorelease(Object _self);
Object Object_Compare(Object _self, Object object);
Object Object_Clone(Object _self);
Object Object_DeepClone(Object _self);
Object Object_TempClone(Object _self);
Object Object_TempDeepClone(Object _self);
Object Object_SetComparator(Object _self, ObjectComparator);
Object Object_SetCloner(Object _self, ObjectCloner);
Object Object_SetDeepCloner(Object _self, ObjectCloner);
Object Object_SetDestructor(Object _self, ObjectDestructor);
Object Object_Hash(Object _self);
Object Object_EmptyComparator(Object _self, Object object);
Object Object_Is(Object _self, Object object);
Object Object_DynamicallyInvoke(Object _self, Object _methodName, ...);

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

