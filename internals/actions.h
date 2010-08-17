#pragma once

#define Action(object, name, parameters...) Object object ##_ ##name (Object receiver, ##parameters)
#define Creator(object) Object object ##_Create()
#define Routine(object, name, Result, parameters...) static inline Result object ##_ ##name (object receiver, ##parameters)

#define DefaultCreator(object) \
Creator(object) \
{ \
	Object toReturn = Object_Create(); \
	toReturn->gid = object ##_GID; \
	SET_ENTITY(toReturn, Allocator_New(allocator, sizeof(struct object))); \
	return object ##_Init(toReturn); \
}
