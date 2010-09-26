#pragma once

#define Action(object, name, parameters...) Object object ##_ ##name (Object receiver, ##parameters)
#define Creator(object) Object object ##_Create()
#define Routine(object, name, Result, parameters...) Result object ##_ ##name (object receiver, ##parameters)

#define DefaultCreator(object) \
Creator(object) \
{ \
	Object toReturn = Object_Create(); \
	toReturn->gid = object ##_GID; \
	SET_ENTITY(toReturn, Allocator_New(allocator, sizeof(struct object))); \
	return object ##_Init(toReturn); \
}

#define DefaultInit(object, actions...) \
Action(object, Init) \
{ \
	Object_SetComparator(receiver, &object ##_Compare); \
	Object_SetCloner(receiver, &object ##_Clone); \
	Object_SetDestructor(receiver, &object ##_Destroy); \
	actions \
	return receiver; \
}

#define DefaultOperations(object) \
Action(object, Clone); \
Action(object, Destroy); \
Action(object, Compare, Object);

#define Defaults(object) \
DefaultOperations(object); \
DefaultInit(object); \
DefaultCreator(object);


